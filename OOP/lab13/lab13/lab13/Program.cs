using System;
using System.IO;
using System.Text.Json;
using System.Xml;
using System.Xml.Linq;
using System.Xml.Serialization;
using System.Collections.Generic;

// Общий интерфейс для сериализаторов
public interface ISerializer
{
    void Serialize<T>(T obj, string filePath);
    T Deserialize<T>(string filePath);
}

// Сериализация в Binary (на основе System.Text.Json)
public class BinarySerializer : ISerializer
{
    public void Serialize<T>(T obj, string filePath)
    {
        var options = new JsonSerializerOptions { WriteIndented = false };
        var binaryData = JsonSerializer.SerializeToUtf8Bytes(obj, options);
        File.WriteAllBytes(filePath, binaryData);
    }

    public T Deserialize<T>(string filePath)
    {
        var binaryData = File.ReadAllBytes(filePath);
        return JsonSerializer.Deserialize<T>(binaryData);
    }
}

// Сериализация в JSON
public class JsonSerializerCustom : ISerializer
{
    public void Serialize<T>(T obj, string filePath)
    {
        var json = JsonSerializer.Serialize(obj);
        File.WriteAllText(filePath, json);
    }

    public T Deserialize<T>(string filePath)
    {
        var json = File.ReadAllText(filePath);
        return JsonSerializer.Deserialize<T>(json);
    }
}

// Сериализация в XML
public class XmlSerializerCustom : ISerializer
{
    public void Serialize<T>(T obj, string filePath)
    {
        var serializer = new XmlSerializer(typeof(T));
        using (var fs = new FileStream(filePath, FileMode.Create))
        {
            serializer.Serialize(fs, obj);
        }
    }

    public T Deserialize<T>(string filePath)
    {
        var serializer = new XmlSerializer(typeof(T));
        using (var fs = new FileStream(filePath, FileMode.Open))
        {
            return (T)serializer.Deserialize(fs);
        }
    }
}

// Абстрактный класс ПечатноеИздание
[Serializable]
public abstract class ПечатноеИздание
{
    public string Название { get; set; }
    public int ГодИздания { get; set; }

    public abstract void Описание();

    public override string ToString()
    {
        return $"Тип: {this.GetType().Name}, Название: {Название}, Год издания: {ГодИздания}";
    }
}

// Класс Книга с запретом сериализации свойства
[Serializable]
public class Книга : ПечатноеИздание
{
    [NonSerialized]
    public string Жанр;

    public override void Описание()
    {
        Console.WriteLine($"Книга: {Название}, жанр: {Жанр}, год издания: {ГодИздания}");
    }
}

class Program
{
    static void Main()
    {
        // Создаем объект Книга
        var книга = new Книга { Название = "Пример книги", ГодИздания = 2021, Жанр = "Фантастика" };

        // Создаем список сериализаторов
        var serializers = new List<ISerializer>
        {
            new BinarySerializer(),
            new JsonSerializerCustom(),
            new XmlSerializerCustom()
        };

        // Сериализация/десериализация
        foreach (var serializer in serializers)
        {
            string extension = serializer.GetType().Name.ToLower().Contains("binary") ? "bin" :
                               serializer.GetType().Name.ToLower().Contains("json") ? "json" : "xml";

            string filePath = $"Книга.{extension}";

            // Сериализация
            serializer.Serialize(книга, filePath);
            Console.WriteLine($"Сериализовано в формат {extension}.");

            // Десериализация
            var десериализованнаяКнига = serializer.Deserialize<Книга>(filePath);
            Console.WriteLine($"Десериализовано из {extension}: {десериализованнаяКнига?.Название}");
        }

        // Работа с XML через XPath
        var xmlSerializer = new XmlSerializerCustom();
        string xmlFilePath = "Книга.xml";
        xmlSerializer.Serialize(книга, xmlFilePath);

        var xmlDoc = new XmlDocument();
        xmlDoc.Load(xmlFilePath);

        var названиеКниги = xmlDoc.SelectSingleNode("//Книга/Название")?.InnerText;
        var годИздания = xmlDoc.SelectSingleNode("//Книга/ГодИздания")?.InnerText;
        Console.WriteLine($"XPath запрос: Название книги: {названиеКниги}, Год издания: {годИздания}");

        // Создание нового XML документа с LINQ to XML
        var newDoc = new XDocument(
            new XElement("Книги",
                new XElement("Книга",
                    new XElement("Название", "Пример книги"),
                    new XElement("ГодИздания", 2021)
                )
            )
        );
        newDoc.Save("НовыйДокумент.xml");

        // LINQ-запрос
        var книги = from книгаNode in newDoc.Descendants("Книга")
                    where (int)книгаNode.Element("ГодИздания") > 2000
                    select книгаNode.Element("Название")?.Value;

        Console.WriteLine("LINQ to XML запросы:");
        foreach (var название in книги)
        {
            Console.WriteLine($"Книга: {название}");
        }
    }
}
