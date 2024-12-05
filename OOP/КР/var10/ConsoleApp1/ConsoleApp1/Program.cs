using System;

namespace Variant10
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

        // 1.А) Создайте перечисление с днями недели и выведите их на консоль.
        static void Task1A()
        {
            Console.WriteLine("Task 1A:");
            foreach (var day in Enum.GetValues(typeof(DaysOfWeek)))
            {
                Console.WriteLine(day);
            }
        }

        // 1.Б) Объедините массив целых чисел в одно число.
        static void Task1B()
        {
            Console.WriteLine("\nTask 1B:");
            int[] numbers = { 1, 2, 3, 4, 5 };
            string result = string.Join("", numbers);
            Console.WriteLine($"Объединенное число: {result}");
        }

        // 2. Класс Computer с полями processor, ram, price.
        static void Task2()
        {
            Console.WriteLine("\nTask 2:");
            Computer c1 = new Computer("Intel", 16, 1200);
            Computer c2 = new Computer("AMD", 8, 800);

            Console.WriteLine($"Сравнение компьютеров:");
            Console.WriteLine(c1.CompareTo(c2) > 0 ? "Первый дороже" : "Второй дороже");
        }

        // 3. Метод расширения Covert(String)
        static void Task3()
        {
            Console.WriteLine("\nTask 3:");
            Computer comp = new Computer("Intel", 16, 1200);
            Console.WriteLine($"Цена в USD: {comp.Convert("USD")}");
            Console.WriteLine($"Цена в EUR: {comp.Convert("EUR")}");
        }
    }

    // 1.А) Перечисление с днями недели
    enum DaysOfWeek
    {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    }

    // 2. Класс Computer
    public class Computer : IComparable<Computer>
    {
        public string Processor { get; }
        public int RAM { get; }
        public int Price { get; }

        public Computer(string processor, int ram, int price)
        {
            Processor = processor;
            RAM = ram;
            Price = price;
        }

        public int CompareTo(Computer other)
        {
            return Price.CompareTo(other.Price);
        }
    }

    // 3. Метод расширения
    public static class ComputerExtensions
    {
        public static string Convert(this Computer computer, string currency)
        {
            double rate = currency == "USD" ? 1.0 : 0.85; // Пример курса
            return $"{computer.Price * rate} {currency}";
        }
    }
}
