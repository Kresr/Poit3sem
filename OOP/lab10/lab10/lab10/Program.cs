using System;
using System.Collections.Generic;
using System.Linq;

public class Book
{
    public string Author { get; set; }
    public int Year { get; set; }
    public int Pages { get; set; }
    public decimal Price { get; set; }
    public string Title { get; set; }
}

public class Program
{
    public static void Main()
    {
        List<Book> books = new List<Book>
        {
            new Book { Author = "Author1", Year = 2001, Pages = 100, Price = 10.99m, Title = "Book1" },
            new Book { Author = "Author2", Year = 1999, Pages = 150, Price = 15.99m, Title = "Book2" },
            new Book { Author = "Author1", Year = 2020, Pages = 200, Price = 20.99m, Title = "Book3" },
            new Book { Author = "Author3", Year = 2015, Pages = 300, Price = 25.99m, Title = "Book4" },
            new Book { Author = "Author2", Year = 2010, Pages = 120, Price = 12.99m, Title = "Book5" }
        };

        // Список книг заданного автора и года
        string specifiedAuthor = "Author1";
        int specifiedYear = 2001;
        var booksByAuthorAndYear = books.Where(b => b.Author == specifiedAuthor && b.Year == specifiedYear);

        // Список книг, выпущенных после заданного года
        int yearThreshold = 2000;
        var booksAfterYear = books.Where(b => b.Year > yearThreshold);

        // Самая тонкая книга
        var thinnestBook = books.OrderBy(b => b.Pages).FirstOrDefault();

        // 5 первых самых толстых книг по низкой цене
        var top5ThickBooks = books.OrderByDescending(b => b.Pages).ThenBy(b => b.Price).Take(5);

        // Список книг, отсортированных по цене
        var booksSortedByPrice = books.OrderBy(b => b.Price);

        // Вывод результатов
        Console.WriteLine("Books by specified author and year:");
        foreach (var book in booksByAuthorAndYear) Console.WriteLine($"{book.Title} by {book.Author}");

        Console.WriteLine("\nBooks published after a specified year:");
        foreach (var book in booksAfterYear) Console.WriteLine($"{book.Title} ({book.Year})");

        Console.WriteLine("\nThe thinnest book:");
        if (thinnestBook != null) Console.WriteLine($"{thinnestBook.Title} with {thinnestBook.Pages} pages");

        Console.WriteLine("\nTop 5 thickest books with the lowest price:");
        foreach (var book in top5ThickBooks) Console.WriteLine($"{book.Title} with {book.Pages} pages at ${book.Price}");

        Console.WriteLine("\nBooks sorted by price:");
        foreach (var book in booksSortedByPrice) Console.WriteLine($"{book.Title} at ${book.Price}");
    }
}
