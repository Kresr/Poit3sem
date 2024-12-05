using System;
using System.Collections.Generic;

namespace Variant3
{
    class Program
    {
        static void Main(string[] args)
        {
            // Вызов каждого задания
            Task1A();
            Task1B();
            Task2();
            Task3();
        }

        // 1.А) Ввести с консоли два числа, сложить их и результат записать в строку
        static void Task1A()
        {
            Console.WriteLine("Task 1A:");
            Console.Write("Введите первое число: ");
            int num1 = int.Parse(Console.ReadLine());
            Console.Write("Введите второе число: ");
            int num2 = int.Parse(Console.ReadLine());
            string result = (num1 + num2).ToString();
            Console.WriteLine($"Результат сложения: {result}");
        }

        // 1.Б) Задать двумерный массив строк. Найти общее количество символов
        static void Task1B()
        {
            Console.WriteLine("\nTask 1B:");
            string[,] array = { { "Hello", "World" }, { "C#", "Programming" } };
            int totalChars = 0;
            foreach (string s in array)
                totalChars += s.Length;
            Console.WriteLine($"Общее количество символов: {totalChars}");
        }

        // 2. Создать класс Point с перегруженными операторами сложения и вычитания
        static void Task2()
        {
            Console.WriteLine("\nTask 2:");
            Point p1 = new Point(1, 2, 3);
            Point p2 = new Point(4, 5, 6);
            Point sum = p1 + p2;
            Point diff = p1 - p2;

            Console.WriteLine($"Сумма точек: {sum}");
            Console.WriteLine($"Разность точек: {diff}");
            Console.WriteLine($"p1 > p2: {p1.CompareTo(p2) > 0}");
            Console.WriteLine($"p1 == p2: {p1.CompareTo(p2) == 0}");
        }

        // 3. Создать интерфейс Graph и реализовать его в Point и Line
        static void Task3()
        {
            Console.WriteLine("\nTask 3:");
            Point[] points = {
                new Point(1, 1, 1),
                new Point(-1, -1, -1),
                new Point(2, 2, 2)
            };
            Line line = new Line(points);
            Console.WriteLine($"Количество точек в первой четверти: {line.First()}");
        }
    }

    public class Point : IComparable<Point>, Graph
    {
        public int X { get; }
        public int Y { get; }
        public int Z { get; }

        public Point(int x, int y, int z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public static Point operator +(Point p1, Point p2) => new Point(p1.X + p2.X, p1.Y + p2.Y, p1.Z + p2.Z);
        public static Point operator -(Point p1, Point p2) => new Point(p1.X - p2.X, p1.Y - p2.Y, p1.Z - p2.Z);

        public int CompareTo(Point other)
        {
            int thisMagnitude = X * X + Y * Y + Z * Z;
            int otherMagnitude = other.X * other.X + other.Y * other.Y + other.Z * other.Z;
            return thisMagnitude.CompareTo(otherMagnitude);
        }

        public int First()
        {
            return (X > 0 && Y > 0 && Z > 0) ? 1 : 0;
        }

        public override string ToString() => $"({X}, {Y}, {Z})";
    }

    public interface Graph
    {
        int First();
    }

    public class Line : Graph
    {
        private Point[] Points;

        public Line(Point[] points)
        {
            Points = points;
        }

        public int First()
        {
            int count = 0;
            foreach (Point point in Points)
            {
                count += point.First();
            }
            return count;
        }
    }
}
