using System;
using System.Linq;
using System.Reflection;
using System.Collections.Generic;
using System.IO;

public class Program
{
    public static void Main(string[] args)
    {
        // Пример использования класса Reflector

        // Работа с классом Person
        string className = "Person";

        // Запись в текстовый файл
        Reflector.WriteToTextFile(className, "person_info.txt");
        Console.WriteLine("Information written to person_info.txt");
    }
}

public class Person
{
    public string Name { get; set; }
    public int Age { get; set; }

    public Person() { }

    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public void SayHello()
    {
        Console.WriteLine($"Hello, my name is {Name} and I am {Age} years old.");
    }

    public void Greet(string greeting)
    {
        Console.WriteLine($"{greeting}, my name is {Name}.");
    }
}

public static class Reflector
{
    // a. Определение имени сборки, в которой определен класс
    public static string GetAssemblyName(string className)
    {
        Type type = Type.GetType(className);
        if (type == null) throw new ArgumentException("Class not found.");
        return type.Assembly.GetName().Name;
    }

    // b. Проверка наличия публичных конструкторов
    public static bool HasPublicConstructors(string className)
    {
        Type type = Type.GetType(className);
        if (type == null) throw new ArgumentException("Class not found.");
        return type.GetConstructors(BindingFlags.Public | BindingFlags.Instance).Any();
    }

    // c. Извлечение всех публичных методов класса
    public static IEnumerable<string> GetPublicMethods(string className)
    {
        Type type = Type.GetType(className);
        if (type == null) throw new ArgumentException("Class not found.");
        return type.GetMethods(BindingFlags.Public | BindingFlags.Instance)
                   .Select(m => m.Name);
    }

    // d. Извлечение полей и свойств класса
    public static IEnumerable<string> GetFieldsAndProperties(string className)
    {
        Type type = Type.GetType(className);
        if (type == null) throw new ArgumentException("Class not found.");

        var fields = type.GetFields(BindingFlags.Public | BindingFlags.Instance)
                         .Select(f => f.Name);
        var properties = type.GetProperties(BindingFlags.Public | BindingFlags.Instance)
                             .Select(p => p.Name);
        return fields.Concat(properties);
    }

    // e. Получение реализованных интерфейсов
    public static IEnumerable<string> GetImplementedInterfaces(string className)
    {
        Type type = Type.GetType(className);
        if (type == null) throw new ArgumentException("Class not found.");
        return type.GetInterfaces().Select(i => i.Name);
    }

    // Запись в текстовый файл
    public static void WriteToTextFile(string className, string filePath)
    {
        using (var writer = new StreamWriter(filePath))
        {
            writer.WriteLine($"Class: {className}");
            writer.WriteLine($"Assembly Name: {GetAssemblyName(className)}");
            writer.WriteLine($"Has Public Constructors: {HasPublicConstructors(className)}");

            writer.WriteLine("\nPublic Methods:");
            foreach (var method in GetPublicMethods(className))
            {
                writer.WriteLine($"- {method}");
            }

            writer.WriteLine("\nFields and Properties:");
            foreach (var item in GetFieldsAndProperties(className))
            {
                writer.WriteLine($"- {item}");
            }

            writer.WriteLine("\nImplemented Interfaces:");
            foreach (var interfaceName in GetImplementedInterfaces(className))
            {
                writer.WriteLine($"- {interfaceName}");
            }
        }
    }
}
