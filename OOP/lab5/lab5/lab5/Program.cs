using System;
using System.Collections.Generic;
using System.Linq;

// Перечисление для типов публикаций
public enum PublicationType
{
    Book,       // Книга
    Magazine,   // Журнал
    Textbook    // Учебник
}

// Структура для описания публикации
public struct Publication
{
    public string Title { get; set; }
    public PublicationType Type { get; set; }
    public int Year { get; set; }
    public decimal Price { get; set; }

    public Publication(string title, PublicationType type, int year, decimal price)
    {
        Title = title;
        Type = type;
        Year = year;
        Price = price;
    }
}

// Partial-класс (первая часть)
public partial class Library
{
    private List<Publication> publications = new List<Publication>();

    public void AddPublication(Publication publication)
    {
        publications.Add(publication);
    }

    public void RemovePublication(Publication publication)
    {
        publications.Remove(publication);
    }

    public List<Publication> GetPublications()
    {
        return publications;
    }

    public void PrintPublications()
    {
        foreach (var pub in publications)
        {
            Console.WriteLine($"{pub.Title}, {pub.Type}, {pub.Year}, {pub.Price:C}");
        }
    }
}

// Partial-класс (вторая часть)
public partial class Library
{
    public decimal CalculateTotalCost()
    {
        return publications.Sum(pub => pub.Price);
    }

    public int CountTextbooks()
    {
        return publications.Count(pub => pub.Type == PublicationType.Textbook);
    }

    public void PrintBooksAfterYear(int year)
    {
        var books = publications.Where(pub => pub.Type == PublicationType.Book && pub.Year >= year);

        Console.WriteLine($"Books published after {year}:");
        foreach (var book in books)
        {
            Console.WriteLine(book.Title);
        }
    }
}

// Класс-контроллер для управления библиотекой
public class LibraryController
{
    private Library library;

    public LibraryController(Library library)
    {
        this.library = library;
    }

    public void AddPublication(Publication publication)
    {
        library.AddPublication(publication);
    }

    public void RemovePublication(Publication publication)
    {
        library.RemovePublication(publication);
    }

    public void DisplayBooksAfterYear(int year)
    {
        library.PrintBooksAfterYear(year);
    }

    public void DisplayTotalTextbooks()
    {
        int count = library.CountTextbooks();
        Console.WriteLine($"Total textbooks: {count}");
    }

    public void DisplayTotalCost()
    {
        decimal totalCost = library.CalculateTotalCost();
        Console.WriteLine($"Total cost of all publications: {totalCost:C}");
    }
}

// Программа для демонстрации работы библиотеки
class Program
{
    static void Main(string[] args)
    {
        // Создаем библиотеку и контроллер для управления ею
        Library library = new Library();
        LibraryController controller = new LibraryController(library);

        // Создаем несколько публикаций
        Publication book1 = new Publication("C# Programming", PublicationType.Book, 2020, 35.50m);
        Publication book2 = new Publication("Algorithms", PublicationType.Book, 2015, 40.00m);
        Publication magazine = new Publication("Tech Today", PublicationType.Magazine, 2018, 5.00m);
        Publication textbook1 = new Publication("Mathematics", PublicationType.Textbook, 2021, 50.00m);
        Publication textbook2 = new Publication("Physics", PublicationType.Textbook, 2019, 45.00m);

        // Добавляем публикации в библиотеку
        controller.AddPublication(book1);
        controller.AddPublication(book2);
        controller.AddPublication(magazine);
        controller.AddPublication(textbook1);
        controller.AddPublication(textbook2);

        
        Console.WriteLine("Книги, вышедшие не ранее 2017 года:");
        controller.DisplayBooksAfterYear(2017);

        Console.WriteLine("\nСуммарное количество учебников:");
        controller.DisplayTotalTextbooks();

        Console.WriteLine("\nОбщая стоимость всех изданий:");
        controller.DisplayTotalCost();
    }
}
