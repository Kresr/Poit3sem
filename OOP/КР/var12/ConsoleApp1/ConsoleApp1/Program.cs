using System;
using System.Linq;

namespace Variant12
{
    class Program
    {
        static void Main(string[] args)
        {
            // Вызов заданий
            Task1A();
            Task1B();
            Task2();
            Task3();
        }

        // 1.А) Введите с консоли строку. Измените ее так, чтобы каждый символ продублировался.
        static void Task1A()
        {
            Console.WriteLine("Task 1A:");
            Console.Write("Введите строку: ");
            string input = Console.ReadLine();
            string doubled = string.Concat(input.Select(c => $"{c}{c}"));
            Console.WriteLine($"Результат: {doubled}");
        }

        // 1.Б) Проинициализируйте двумерный массив целых чисел. Посчитайте, сколько положительных.
        static void Task1B()
        {
            Console.WriteLine("\nTask 1B:");
            int[,] array = { { -1, 2 }, { 3, -4 }, { 5, 6 } };
            int positiveCount = 0;
            foreach (int num in array)
            {
                if (num > 0) positiveCount++;
            }
            Console.WriteLine($"Количество положительных чисел: {positiveCount}");
        }

        // 2. Класс Bag с методом расширения для обнуления суммы.
        static void Task2()
        {
            Console.WriteLine("\nTask 2:");
            Bag bag1 = new Bag("Bag1", 500);
            Bag bag2 = new Bag("Bag2", 300);

            Console.WriteLine($"Bag1 > Bag2: {bag1.CompareTo(bag2) > 0}");
            bag1.SetSum(0);  // Используем метод SetSum для обнуления
            Console.WriteLine($"Bag1 сумма после сброса: {bag1.Sum}");
        }

        // 3. Реализация интерфейса IBank в Bag и Cassa.
        static void Task3()
        {
            Console.WriteLine("\nTask 3:");
            Cassa cassa = new Cassa("Cassa", 1000);

            Console.WriteLine($"Минус (Bag): {cassa.Minus(100)}");
            Console.WriteLine($"Минус (Cassa): {((IBank)cassa).Minus(100)}");
        }
    }

    // Класс Bag
    public class Bag : IComparable<Bag>, IBank
    {
        public string Name { get; }
        public int Sum { get; private set; }

        public Bag(string name, int sum)
        {
            Name = name;
            Sum = sum;
        }

        public int CompareTo(Bag other)
        {
            return Sum.CompareTo(other.Sum);
        }

        // Метод для изменения суммы
        public void SetSum(int newSum)
        {
            Sum = newSum;
        }

        public virtual int Minus(int sum)
        {
            return (int)(sum * 0.9); // возвращает 90% от переданной суммы
        }
    }

    // Расширение для обнуления суммы
    public static class BagExtensions
    {
        public static void Reset(this Bag bag)
        {
            bag.SetSum(0); // Сбрасываем сумму через SetSum
        }
    }

    // Интерфейс IBank
    public interface IBank
    {
        int Minus(int sum);
    }

    // Класс Cassa, который реализует IBank
    public class Cassa : Bag, IBank
    {
        public Cassa(string name, int sum) : base(name, sum) { }

        // Реализация метода Minus для Cassa (возвращает 50% от переданной суммы)
        int IBank.Minus(int sum)
        {
            return (int)(sum * 0.5); // возвращает 50% от переданной суммы
        }
    }
}
