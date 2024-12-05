using System;

namespace Variant9
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

        // 1.А) Создайте перечисление с месяцами и выведите их на консоль.
        static void Task1A()
        {
            Console.WriteLine("Task 1A:");
            foreach (var month in Enum.GetValues(typeof(Months)))
            {
                Console.WriteLine(month);
            }
        }

        // 1.Б) Разбейте строку на три по предложениям.
        static void Task1B()
        {
            Console.WriteLine("\nTask 1B:");
            string input = "123.345.678";
            string[] parts = input.Split('.');
            foreach (string part in parts)
                Console.WriteLine(part);
        }

        // 2. Создать класс Computer с тремя полями и реализовать интерфейс IComparable.
        static void Task2()
        {
            Console.WriteLine("\nTask 2:");
            Computer c1 = new Computer("Intel", 16, 1000);
            Computer c2 = new Computer("AMD", 8, 800);

            Console.WriteLine($"Сравнение компьютеров:");
            Console.WriteLine(c1.CompareTo(c2) > 0 ? "Первый дороже" : "Второй дороже");
        }

        // 3. Создать интерфейс IGood и абстрактный класс Something.
        static void Task3()
        {
            Console.WriteLine("\nTask 3:");
            Case myCase = new Case();
            myCase.ItsOk();
            myCase.Fine();
        }
    }

    // 1.А) Перечисление с месяцами
    enum Months
    {
        January,
        February,
        March,
        April,
        May,
        June,
        July,
        August,
        September,
        October,
        November,
        December
    }

    // 2. Класс Computer
    public class Computer : IComparable<Computer>
    {
        public string Processor { get; }
        public static int StaticValue { get; } = 100;
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

    // 3. Интерфейс и абстрактный класс
    public interface IGood
    {
        void Fine();
    }

    public abstract class Something
    {
        public abstract void ItsOk();
    }

    public class Case : Something, IGood
    {
        public override void ItsOk()
        {
            Console.WriteLine("Метод ItsOk() выполнен.");
        }

        public void Fine()
        {
            Console.WriteLine("Метод Fine() выполнен.");
        }
    }
}
