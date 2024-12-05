using System;
using System.Collections.Concurrent;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

class Program
{
    static async Task Main(string[] args)
    {
        // 1. Длительная задача с использованием TPL (решето Эратосфена)
        await RunSieveOfEratosthenesTask();

        // 2. Задача с токеном отмены (CancellationToken)
        await RunTaskWithCancellation();

        // 3. Задачи с возвратом результата
        await RunTasksWithReturnResult();

        // 4. Задачи продолжения (Continuation Task)
        await RunContinuationTask();

        // 5. Параллельные вычисления с использованием Parallel
        RunParallelForExample();

        // 6. Использование Parallel.Invoke()
        RunParallelInvokeExample();

        // 7. BlockingCollection: Поставщики и покупатели
        await RunBlockingCollectionExample();

        // 8. Асинхронные методы с async/await
        await RunAsyncAwaitExample();
    }

    // 1. Длительная задача с использованием TPL (решето Эратосфена)
    static async Task RunSieveOfEratosthenesTask()
    {
        Stopwatch stopwatch = new Stopwatch();
        stopwatch.Start();

        Task task = Task.Run(() => SieveOfEratosthenes(1000000));
        Console.WriteLine($"Идентификатор задачи: {task.Id}");

        while (!task.IsCompleted)
        {
            Console.WriteLine($"Задача {task.Id} в процессе выполнения. Статус: {task.Status}");
            await Task.Delay(500);
        }

        stopwatch.Stop();
        Console.WriteLine($"Задача завершена. Статус: {task.Status}");
        Console.WriteLine($"Время выполнения задачи: {stopwatch.ElapsedMilliseconds} мс");
    }

    static void SieveOfEratosthenes(int n)
    {
        bool[] sieve = new bool[n + 1];
        for (int i = 2; i <= n; i++) sieve[i] = true;

        for (int i = 2; i * i <= n; i++)
        {
            if (sieve[i])
            {
                for (int j = i * i; j <= n; j += i)
                {
                    sieve[j] = false;
                }
            }
        }

        // Опционально выводим первые несколько простых чисел
        for (int i = 2; i <= n; i++)
        {
            if (sieve[i])
                Console.Write(i + " ");
        }
    }

    // 2. Задача с токеном отмены (CancellationToken)
    static async Task RunTaskWithCancellation()
    {
        CancellationTokenSource cancellationTokenSource = new CancellationTokenSource();
        Stopwatch stopwatch = new Stopwatch();
        stopwatch.Start();

        Task task = Task.Run(() => SieveWithCancellation(1000000, cancellationTokenSource.Token));

        await Task.Delay(2000);
        cancellationTokenSource.Cancel();

        await task;

        stopwatch.Stop();
        Console.WriteLine($"Задача завершена. Время выполнения: {stopwatch.ElapsedMilliseconds} мс");
    }

    static void SieveWithCancellation(int n, CancellationToken cancellationToken)
    {
        bool[] sieve = new bool[n + 1];
        for (int i = 2; i <= n; i++) sieve[i] = true;

        for (int i = 2; i * i <= n; i++)
        {
            if (cancellationToken.IsCancellationRequested)
            {
                Console.WriteLine("Задача отменена.");
                return;
            }

            if (sieve[i])
            {
                for (int j = i * i; j <= n; j += i)
                {
                    sieve[j] = false;
                }
            }
        }
    }

    // 3. Задачи с возвратом результата
    static async Task RunTasksWithReturnResult()
    {
        Task<int> task1 = Task.Run(() => CalculateSum(1, 1000));
        Task<int> task2 = Task.Run(() => CalculateSum(1001, 2000));
        Task<int> task3 = Task.Run(() => CalculateSum(2001, 3000));

        int[] results = await Task.WhenAll(task1, task2, task3);

        int totalSum = results[0] + results[1] + results[2];
        Console.WriteLine($"Общая сумма: {totalSum}");
    }

    static int CalculateSum(int start, int end)
    {
        int sum = 0;
        for (int i = start; i <= end; i++)
        {
            sum += i;
        }
        return sum;
    }

    // 4. Задачи продолжения (Continuation Task)
    static async Task RunContinuationTask()
    {
        Task<int> task = Task.Run(() => 5 * 5);

        task.ContinueWith(t =>
        {
            Console.WriteLine($"Результат из продолженной задачи: {t.Result}");
        });

        var awaiter = task.GetAwaiter();
        awaiter.OnCompleted(() =>
        {
            Console.WriteLine($"Результат из продолженной задачи с GetAwaiter: {awaiter.GetResult()}");
        });

        await task;
    }

    // 5. Параллельные вычисления с использованием Parallel
    static void RunParallelForExample()
    {
        int[] numbers = Enumerable.Range(1, 1000000).ToArray();

        Parallel.For(0, numbers.Length, i =>
        {
            numbers[i] = numbers[i] * 2;
        });

        Console.WriteLine("Обработка завершена.");
    }

    // 6. Использование Parallel.Invoke()
    static void RunParallelInvokeExample()
    {
        Parallel.Invoke(
            () => Console.WriteLine("Блок 1 выполняется"),
            () => Console.WriteLine("Блок 2 выполняется"),
            () => Console.WriteLine("Блок 3 выполняется")
        );
    }

    // 7. BlockingCollection: Поставщики и покупатели
    static async Task RunBlockingCollectionExample()
    {
        BlockingCollection<string> warehouse = new BlockingCollection<string>(5);
        int maxItemsPerSupplier = 10; // Максимум товаров, которые поставщик может добавить
        int maxBuyAttempts = 20;      // Максимум попыток покупки для каждого покупателя

        // Поставщики
        var suppliers = new Task[5];
        for (int i = 0; i < 5; i++)
        {
            int supplierId = i;
            suppliers[i] = Task.Run(() =>
            {
                for (int j = 0; j < maxItemsPerSupplier; j++)
                {
                    var item = $"Товар {supplierId}-{j}";
                    warehouse.Add(item);
                    Console.WriteLine($"Поставщик {supplierId} добавил {item}");
                    Thread.Sleep(500); // Скорость завоза товара
                }
            });
        }

        // Покупатели
        var buyers = new Task[10];
        for (int i = 0; i < 10; i++)
        {
            int buyerId = i;
            buyers[i] = Task.Run(() =>
            {
                for (int j = 0; j < maxBuyAttempts; j++)
                {
                    if (warehouse.TryTake(out var item))
                    {
                        Console.WriteLine($"Покупатель {buyerId} купил {item}");
                    }
                    else
                    {
                        Console.WriteLine($"Покупатель {buyerId} ушел, товара нет");
                    }
                    Thread.Sleep(300); // Скорость покупки
                }
            });
        }

        // Дождаться завершения всех поставщиков и покупателей
        await Task.WhenAll(suppliers.Concat(buyers));
        Console.WriteLine("Все операции завершены.");
    }


    // 8. Асинхронные методы с async/await
    static async Task RunAsyncAwaitExample()
    {
        Console.WriteLine("Запуск асинхронной задачи...");
        var result = await CalculateAsync();
        Console.WriteLine($"Результат: {result}");
    }

    static async Task<int> CalculateAsync()
    {
        await Task.Delay(30); // Имитируем длительную операцию
        return 42;
    }
}
