using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Threading;

class Program
{
    static void Main(string[] args)
    {
        // 1. Список запущенных процессов
        PrintRunningProcesses();

        // 2. Работа с доменом приложения
        ExploreAppDomain();

        // 3. Работа с потоками (генерация простых чисел)
        ThreadTaskWithPrimes();

        // 4. Два потока для четных и нечетных чисел
        ThreadTaskWithEvenOddNumbers();

        // 5. Повторяющаяся задача с использованием Timer
        TimerTask();

        Console.WriteLine("Все задания выполнены.");
    }

    // 1. Список запущенных процессов
    static void PrintRunningProcesses()
    {
        Console.WriteLine("Список запущенных процессов:");

        var processes = Process.GetProcesses();

        try
        {
            // Открываем поток для записи в файл
            using (StreamWriter writer = new StreamWriter("processes.txt", false))
            {
                // Пройдем по каждому процессу
                foreach (var process in processes)
                {
                    try
                    {
                        // Сбор информации о процессе
                        string processInfo = $"ID: {process.Id}, Имя: {process.ProcessName}, " +
                                             $"Приоритет: {process.BasePriority}, " +
                                             $"Состояние: {(process.Responding ? "Отвечает" : "Не отвечает")}, " +
                                             $"Время запуска: {process.StartTime}, " +
                                             $"Время использования ЦП: {process.TotalProcessorTime}";

                        // Выводим информацию на консоль
                        Console.WriteLine(processInfo);

                        // Записываем в файл
                        writer.WriteLine(processInfo);
                    }
                    catch (Exception ex)
                    {
                        // Если возникла ошибка при получении данных о процессе
                        string errorInfo = $"ID: {process.Id}, Имя: {process.ProcessName} - доступ запрещен ({ex.Message})";

                        // Выводим ошибку на консоль
                        Console.WriteLine(errorInfo);

                        // Записываем ошибку в файл
                        writer.WriteLine(errorInfo);
                    }
                }

                // Обязательно сбрасываем данные в файл
                writer.Flush();
            }
        }
        catch (Exception ex)
        {
            // Ошибка при работе с файлом
            Console.WriteLine($"Ошибка при записи процессов в файл: {ex.Message}");
        }

        // Сообщаем пользователю, что данные записаны в файл
        Console.WriteLine("Процессы записаны в файл 'processes.txt'.");
    }

    // 2. Работа с доменом приложения
    static void ExploreAppDomain()
    {
        Console.WriteLine("Исследование текущего домена приложения:");

        AppDomain currentDomain = AppDomain.CurrentDomain;

        Console.WriteLine($"Имя домена: {currentDomain.FriendlyName}");
        Console.WriteLine("Загруженные сборки:");
        foreach (var assembly in currentDomain.GetAssemblies())
        {
            Console.WriteLine($"Сборка: {assembly.FullName}");
        }

        // Создание нового домена
        try
        {
            AppDomain newDomain = AppDomain.CreateDomain("NewDomain");
            Console.WriteLine($"Создан новый домен: {newDomain.FriendlyName}");

            try
            {
                // Попытка загрузить сборку в новый домен
                newDomain.Load("System.Xml");
                Console.WriteLine("Сборка System.Xml загружена в новый домен.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при загрузке сборки: {ex.Message}");
            }

            // Выгрузка нового домена
            AppDomain.Unload(newDomain);
            Console.WriteLine("Новый домен выгружен.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при создании нового домена: {ex.Message}");
        }
    }

    // 3. Работа с потоками (генерация простых чисел)
    static void ThreadTaskWithPrimes()
    {
        Console.WriteLine("Введите n для генерации простых чисел:");
        int n;
        if (!int.TryParse(Console.ReadLine(), out n))
        {
            Console.WriteLine("Ошибка ввода! Пожалуйста, введите целое число.");
            return;
        }

        try
        {
            Thread primeThread = new Thread(() => GeneratePrimes(n));
            primeThread.Start();

            primeThread.Join();
            Console.WriteLine("Поток завершен.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при работе с потоком: {ex.Message}");
        }
    }

    // Генерация простых чисел
    static void GeneratePrimes(int n)
    {
        try
        {
            using (StreamWriter writer = new StreamWriter("primes.txt"))
            {
                for (int i = 2; i <= n; i++)
                {
                    if (IsPrime(i))
                    {
                        Console.WriteLine(i);
                        writer.WriteLine(i);
                        Thread.Sleep(50); // Искусственная задержка
                    }
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при генерации простых чисел: {ex.Message}");
        }
    }

    // Проверка числа на простоту
    static bool IsPrime(int num)
    {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0) return false;
        }
        return true;
    }

    // 4. Два потока для четных и нечетных чисел
    static void ThreadTaskWithEvenOddNumbers()
    {
        Console.WriteLine("Введите n для четных и нечетных чисел:");
        int n;
        if (!int.TryParse(Console.ReadLine(), out n))
        {
            Console.WriteLine("Ошибка ввода! Пожалуйста, введите целое число.");
            return;
        }

        try
        {
            using (StreamWriter writer = new StreamWriter("even_odd.txt"))
            {
                object locker = new object();
                Thread evenThread = new Thread(() => WriteNumbers(writer, locker, n, true));
                Thread oddThread = new Thread(() => WriteNumbers(writer, locker, n, false));

                evenThread.Priority = ThreadPriority.AboveNormal; // Установка приоритета
                evenThread.Start();
                oddThread.Start();

                evenThread.Join();
                oddThread.Join();
            }

            Console.WriteLine("Четные и нечетные числа записаны в файл 'even_odd.txt'.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при работе с потоками для четных и нечетных чисел: {ex.Message}");
        }
    }

    // Запись четных и нечетных чисел
    static void WriteNumbers(StreamWriter writer, object locker, int n, bool isEven)
    {
        try
        {
            for (int i = isEven ? 2 : 1; i <= n; i += 2)
            {
                lock (locker)
                {
                    Console.WriteLine(i);
                    writer.WriteLine(i);
                }
                Thread.Sleep(isEven ? 30 : 50); // Разная скорость расчета
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при записи чисел: {ex.Message}");
        }
    }

    // 5. Повторяющаяся задача с использованием Timer
    static void TimerTask()
    {
        Console.WriteLine("Запуск задачи на основе Timer.");
        try
        {
            Timer timer = new Timer(TimerCallback, null, 0, 2000);

            Console.WriteLine("Нажмите Enter для завершения таймера...");
            Console.ReadLine();
            timer.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при работе с таймером: {ex.Message}");
        }
    }

    // Callback для таймера
    static void TimerCallback(object state)
    {
        try
        {
            Console.WriteLine($"Таймер вызван в {DateTime.Now}");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка в таймере: {ex.Message}");
        }
    }
}
