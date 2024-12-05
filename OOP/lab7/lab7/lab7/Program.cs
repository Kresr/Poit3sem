using System;
using System.Collections.Generic;
using System.IO;

// Объявление интерфейса IPersona
public interface IPersona
{
    // Метод интерфейса, который должен быть реализован
    string GetPersonaInfo();
}

// Обобщённый интерфейс с операциями добавить, удалить, просмотреть
public interface IGenericOperations<T>
{
    void Add(T item);
    void Remove(T item);
    void View();
}

// Обобщённый класс CollectionType<T> без ограничения на тип
public class CollectionType<T> : IGenericOperations<T>
{
    private List<T> collection = new List<T>();

    // Добавление элемента в коллекцию
    public void Add(T item)
    {
        try
        {
            collection.Add(item);
            Console.WriteLine($"{item} был добавлен в коллекцию.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при добавлении элемента: {ex.Message}");
        }
        finally
        {
            Console.WriteLine("Операция добавления завершена.");
        }
    }

    // Удаление элемента из коллекции
    public void Remove(T item)
    {
        try
        {
            if (collection.Contains(item))
            {
                collection.Remove(item);
                Console.WriteLine($"{item} был удалён из коллекции.");
            }
            else
            {
                Console.WriteLine($"{item} не найден в коллекции.");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при удалении элемента: {ex.Message}");
        }
        finally
        {
            Console.WriteLine("Операция удаления завершена.");
        }
    }

    // Просмотр всех элементов в коллекции
    public void View()
    {
        try
        {
            if (collection.Count == 0)
            {
                Console.WriteLine("Коллекция пуста.");
            }
            else
            {
                Console.WriteLine("Содержимое коллекции:");
                foreach (var item in collection)
                {
                    Console.WriteLine(item);
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при просмотре коллекции: {ex.Message}");
        }
        finally
        {
            Console.WriteLine("Операция просмотра завершена.");
        }
    }

    // Метод для сохранения коллекции в текстовый файл
    public void SaveToFile(string filename)
    {
        try
        {
            using (StreamWriter writer = new StreamWriter(filename))
            {
                foreach (var item in collection)
                {
                    writer.WriteLine(item);
                }
            }
            Console.WriteLine($"Коллекция сохранена в файл {filename}.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при сохранении в файл: {ex.Message}");
        }
    }

    // Метод для загрузки коллекции из текстового файла
    public void LoadFromFile(string filename)
    {
        try
        {
            using (StreamReader reader = new StreamReader(filename))
            {
                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    Console.WriteLine($"Прочитано из файла: {line}");
                    // Здесь можно добавить логику для восстановления объекта, если необходимо
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при чтении из файла: {ex.Message}");
        }
    }
}

// Класс Person, реализующий интерфейс IPersona
public class Person : IPersona
{
    public string Name { get; set; }
    public int Age { get; set; }

    // Реализация метода интерфейса IPersona
    public virtual string GetPersonaInfo()
    {
        return $"Имя: {Name}, Возраст: {Age}";
    }

    // Переопределение метода ToString
    public override string ToString()
    {
        return $"Персона: {Name}, возраст: {Age}";
    }
}

// Класс Author, наследующий Person
public class Author : Person
{
    public string BookAuthor { get; set; }

    // Переопределение метода GetPersonaInfo
    public override string GetPersonaInfo()
    {
        return $"{base.GetPersonaInfo()}, Автор книги: {BookAuthor}";
    }
}

// Класс PublishingHouse, наследующий Person (запрещён для наследования)
public sealed class PublishingHouse : Person
{
    public string PublishingHouseName { get; set; }

    // Переопределение метода GetPersonaInfo
    public override string GetPersonaInfo()
    {
        return $"{base.GetPersonaInfo()}, Издательство: {PublishingHouseName}";
    }
}

// Тестирование обобщённого класса
class Program
{
    static void Main()
    {
        // Использование обобщённого типа с классом Person
        CollectionType<Person> personsCollection = new CollectionType<Person>();
        Person person1 = new Person { Name = "Anna", Age = 30 };
        Author author = new Author { Name = "Ivan Ivanov", Age = 45, BookAuthor = "Programming C#" };

        // Добавление объектов
        personsCollection.Add(person1);
        personsCollection.Add(author);

        // Просмотр объектов в коллекции
        personsCollection.View();

        // Удаление объекта
        personsCollection.Remove(person1);

        // Сохранение коллекции в файл
        personsCollection.SaveToFile("collection.txt");

        // Чтение коллекции из файла
        personsCollection.LoadFromFile("collection.txt");

        // Тестирование обобщённого класса с целыми числами
        CollectionType<int?> intCollection = new CollectionType<int?>();
        intCollection.Add(10);
        intCollection.Add(20);
        intCollection.View();
        intCollection.SaveToFile("intCollection.txt");
    }
}
