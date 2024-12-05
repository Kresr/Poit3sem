using System;

// Интерфейс IPersona
public interface IPersona
{
    // Метод интерфейса, который должен быть реализован в классах, наследующих этот интерфейс
    string GetPersonaInfo();
}

// Абстрактный класс ПечатноеИздание
public abstract class ПечатноеИздание
{
    public string Название { get; set; }
    public int ГодИздания { get; set; }

    // Абстрактный метод, который должен быть переопределен в производных классах
    public abstract void Описание();

    // Переопределение метода ToString()
    public override string ToString()
    {
        return $"Тип: {this.GetType().Name}, Название: {Название}, Год издания: {ГодИздания}";
    }
}

// Производные классы от ПечатноеИздание

public class Книга : ПечатноеИздание
{
    public string Жанр { get; set; }

    // Переопределение абстрактного метода Описание
    public override void Описание()
    {
        Console.WriteLine($"Книга: {Название}, жанр: {Жанр}, год издания: {ГодИздания}");
    }
}

public class Учебник : ПечатноеИздание
{
    public string Предмет { get; set; }

    // Переопределение абстрактного метода Описание
    public override void Описание()
    {
        Console.WriteLine($"Учебник: {Название}, предмет: {Предмет}, год издания: {ГодИздания}");
    }
}

public class Журнал : ПечатноеИздание
{
    public int ВыпускНомер { get; set; }

    // Переопределение абстрактного метода Описание
    public override void Описание()
    {
        Console.WriteLine($"Журнал: {Название}, выпуск №{ВыпускНомер}, год издания: {ГодИздания}");
    }
}

// Класс Персона, который реализует интерфейс IPersona
public class Персона : IPersona
{
    public string Имя { get; set; }
    public int Возраст { get; set; }

    // Реализация метода интерфейса IPersona
    public virtual string GetPersonaInfo()
    {
        return $"Имя: {Имя}, Возраст: {Возраст}";
    }

    // Переопределение метода ToString()
    public override string ToString()
    {
        return $"Персона: {Имя}, возраст: {Возраст}";
    }
}

// Производные классы от Персона

public class Автор : Персона
{
    public string КнигаАвтор { get; set; }

    // Переопределение метода интерфейса GetPersonaInfo
    public override string GetPersonaInfo()
    {
        return $"{base.GetPersonaInfo()}, автор книги: {КнигаАвтор}";
    }
}

// Класс Издательство сделан sealed
public sealed class Издательство : Персона
{
    public string НазваниеИздательства { get; set; }

    // Переопределение метода интерфейса GetPersonaInfo
    public override string GetPersonaInfo()
    {
        return $"{base.GetPersonaInfo()}, издательство: {НазваниеИздательства}";
    }
}

// Класс Printer для полиморфного вывода информации о печатных изданиях
public class Printer
{
    // Полиморфный метод, принимающий объект ПечатноеИздание или его производные классы
    public void IAmPrinting(ПечатноеИздание издание)
    {
        Console.WriteLine(издание.ToString());
    }
}

// Демонстрационная программа
class Program
{
    static void Main()
    {
        // Создаем объекты различных классов
        Книга книга = new Книга { Название = "C# для начинающих", ГодИздания = 2021, Жанр = "Образование" };
        Учебник учебник = new Учебник { Название = "Математика", ГодИздания = 2019, Предмет = "Алгебра" };
        Журнал журнал = new Журнал { Название = "Наука и техника", ГодИздания = 2022, ВыпускНомер = 5 };
        Автор автор = new Автор { Имя = "Иван Иванов", Возраст = 45, КнигаАвтор = "C# для начинающих" };
        Издательство издательство = new Издательство { Имя = "Петр Петров", Возраст = 55, НазваниеИздательства = "Издательский дом" };

        // Создаем объект Printer
        Printer printer = new Printer();

        // Массив объектов ПечатноеИздание
        ПечатноеИздание[] издания = { книга, учебник, журнал };

        // Вызов метода IAmPrinting для каждого объекта
        foreach (var издание in издания)
        {
            printer.IAmPrinting(издание);
        }
    }
}
