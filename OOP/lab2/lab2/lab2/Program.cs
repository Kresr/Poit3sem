using System;
using System.Collections.Generic;

public partial class Book
{
    // Поля
    private readonly int id; // Поле только для чтения
    private static int nextId = 1; // Для генерации уникального ID
    private string title;
    private string author;
    private string publisher;
    private int year;
    private int pageCount;
    private decimal price;
    private string bindingType;

    // Поле-константа
    public const string Category = "Литература";

    // Статическое поле для подсчета количества объектов
    private static int bookCount;

    // Свойства
    public int Id => id; // Только для чтения
    public string Title
    {
        get { return title; }
        set { title = value; }
    }
    public string Author
    {
        get { return author; }
        set { author = value; }
    }
    public string Publisher
    {
        get { return publisher; }
        set { publisher = value; }
    }
    public int Year
    {
        get { return year; }
        set
        {
            if (value > 0) year = value;
            else throw new ArgumentException("Год издания должен быть положительным.");
        }
    }
    public int PageCount
    {
        get { return pageCount; }
        set
        {
            if (value > 0) pageCount = value;
            else throw new ArgumentException("Количество страниц должно быть положительным.");
        }
    }
    public decimal Price
    {
        get { return price; }
        set
        {
            if (value >= 0) price = value;
            else throw new ArgumentException("Цена должна быть неотрицательной.");
        }
    }
    public string BindingType
    {
        get { return bindingType; }
        set { bindingType = value; }
    }

    // Конструкторы
    public Book()
    {
        id = nextId++;
        bookCount++;
    }

    public Book(string title, string author, string publisher, int year, int pageCount, decimal price, string bindingType)
        : this()
    {
        Title = title;
        Author = author;
        Publisher = publisher;
        Year = year;
        PageCount = pageCount;
        Price = price;
        BindingType = bindingType;
    }

    public Book(string title, string author)
        : this(title, author, "Неизвестное издательство", 2000, 100, 10.0m, "Твердый переплет")
    {
    }

    // Закрытый конструктор
    private Book(int id)
    {
        this.id = id;
    }

    // Статический метод для создания через закрытый конструктор
    public static Book CreateBookWithId(int id)
    {
        return new Book(id);
    }

    // Статический конструктор
    static Book()
    {
        bookCount = 0;
    }

    // Метод для поиска книг по автору
    public static List<Book> GetBooksByAuthor(List<Book> books, string author)
    {
        return books.FindAll(b => b.Author == author);
    }

    // Метод для поиска книг, выпущенных после заданного года
    public static List<Book> GetBooksAfterYear(List<Book> books, int year)
    {
        return books.FindAll(b => b.Year > year);
    }

    // Статический метод для вывода информации о классе
    public static void PrintBookCount()
    {
        Console.WriteLine($"Общее количество книг: {bookCount}");
    }

    // Использование ref и out
    public void UpdatePrice(ref decimal newPrice, out decimal oldPrice)
    {
        oldPrice = Price;
        Price = newPrice;
    }

    // Переопределенные методы
    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Book other = (Book)obj;
        return id == other.id;
    }

    public override int GetHashCode()
    {
        return id.GetHashCode();
    }

    public override string ToString()
    {
        return $"Книга[ID={id}, Название={title}, Автор={author}, Год={year}, Цена={price}]";
    }
}

// Вторая часть partial класса (можно расширять в других файлах)
public partial class Book
{
    public void DisplayInfo()
    {
        Console.WriteLine(ToString());
    }
}

// Пример использования
class Program
{
    static void Main(string[] args)
    {
        // Создание объектов
        Book book1 = new Book("Война и мир", "Лев Толстой", "Пингвин", 1869, 1225, 20.0m, "Твердый переплет");
        Book book2 = new Book("Анна Каренина", "Лев Толстой");

        List<Book> books = new List<Book> { book1, book2 };

        // Вывод книг по автору
        var tolstoyBooks = Book.GetBooksByAuthor(books, "Лев Толстой");
        Console.WriteLine("Книги Льва Толстого:");
        foreach (var book in tolstoyBooks)
        {
            Console.WriteLine(book);
        }

        // Обновление цены
        decimal newPrice = 25.0m;
        book1.UpdatePrice(ref newPrice, out decimal oldPrice);
        Console.WriteLine($"Старая цена: {oldPrice}, Новая цена: {book1.Price}");

        // Вывод информации о книгах
        Book.PrintBookCount();
    }
}
