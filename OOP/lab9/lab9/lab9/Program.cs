using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

// Класс Computer с основными свойствами и методами
public class Computer : IEquatable<Computer>
{
    public string Processor { get; set; }
    public int RAM { get; set; }
    public int Storage { get; set; }

    public Computer(string processor, int ram, int storage)
    {
        Processor = processor;
        RAM = ram;
        Storage = storage;
    }

    public override string ToString()
    {
        return $"Computer: Processor = {Processor}, RAM = {RAM} GB, Storage = {Storage} GB";
    }

    public bool Equals(Computer other)
    {
        if (other == null) return false;
        return this.Processor == other.Processor && this.RAM == other.RAM && this.Storage == other.Storage;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Processor, RAM, Storage);
    }
}

// Класс для управления коллекцией объектов Computer
public class ComputerCollection
{
    private ISet<Computer> computers;

    public ComputerCollection()
    {
        computers = new HashSet<Computer>();
    }

    public void AddComputer(Computer computer)
    {
        if (computers.Add(computer))
        {
            Console.WriteLine("Computer added successfully.");
        }
        else
        {
            Console.WriteLine("Computer already exists in the collection.");
        }
    }

    public void RemoveComputer(Computer computer)
    {
        if (computers.Remove(computer))
        {
            Console.WriteLine("Computer removed successfully.");
        }
        else
        {
            Console.WriteLine("Computer not found in the collection.");
        }
    }

    public void ShowComputers()
    {
        if (computers.Count == 0)
        {
            Console.WriteLine("No computers in the collection.");
        }
        else
        {
            foreach (var computer in computers)
            {
                Console.WriteLine(computer);
            }
        }
    }

    public Computer FindComputer(Func<Computer, bool> criteria)
    {
        foreach (var computer in computers)
        {
            if (criteria(computer))
                return computer;
        }
        return null;
    }
}

public class Program
{
    public static void Main(string[] args)
    {
        // 1. Работа с классом Computer и коллекцией ComputerCollection
        var computerCollection = new ComputerCollection();
        computerCollection.AddComputer(new Computer("Intel i7", 16, 512));
        computerCollection.AddComputer(new Computer("AMD Ryzen 5", 8, 256));
        computerCollection.ShowComputers();

        // 2. Работа с коллекцией Queue<int>
        Queue<int> numberQueue = new Queue<int>();
        for (int i = 1; i <= 10; i++)
        {
            numberQueue.Enqueue(i);
        }

        // a. Вывод коллекции на консоль
        Console.WriteLine("Initial number queue:");
        foreach (var number in numberQueue)
        {
            Console.Write(number + " ");
        }
        Console.WriteLine();

        // b. Удаление n последовательных элементов
        int n = 3;
        Console.WriteLine($"Removing {n} elements from the queue:");
        for (int i = 0; i < n; i++)
        {
            if (numberQueue.Count > 0)
            {
                Console.WriteLine($"Removed: {numberQueue.Dequeue()}");
            }
        }

        // c. Добавление новых элементов
        numberQueue.Enqueue(11);
        numberQueue.Enqueue(12);
        numberQueue.Enqueue(13);

        // d. Создание второй коллекции Queue<int> и копирование данных
        Queue<int> secondQueue = new Queue<int>(numberQueue);

        // e. Вывод второй коллекции
        Console.WriteLine("Second number queue:");
        foreach (var number in secondQueue)
        {
            Console.Write(number + " ");
        }
        Console.WriteLine();

        // f. Поиск элемента в коллекции
        int searchValue = 11;
        bool found = secondQueue.Contains(searchValue);
        Console.WriteLine($"Element {searchValue} is {(found ? "found" : "not found")} in the second queue.");

        // 3. Работа с ObservableCollection<Computer>
        ObservableCollection<Computer> observableCollection = new ObservableCollection<Computer>();
        observableCollection.CollectionChanged += ObservableCollection_CollectionChanged;

        // Добавление элементов
        observableCollection.Add(new Computer("Intel i5", 16, 512));
        observableCollection.Add(new Computer("AMD Ryzen 7", 32, 1024));

        // Удаление элемента
        observableCollection.RemoveAt(0);
    }

    // Метод, подписанный на событие изменения коллекции
    private static void ObservableCollection_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
    {
        if (e.Action == NotifyCollectionChangedAction.Add)
        {
            Console.WriteLine("A new item was added to the collection.");
        }
        else if (e.Action == NotifyCollectionChangedAction.Remove)
        {
            Console.WriteLine("An item was removed from the collection.");
        }
    }
}
