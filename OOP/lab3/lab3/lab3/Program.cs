using System;
using System.Collections.Generic;
using System.Linq;

// Основной класс List
class MyList
{
    private List<int> _list;

    // Конструктор по умолчанию
    public MyList()
    {
        _list = new List<int>();
    }

    // Конструктор с инициализацией списка
    public MyList(IEnumerable<int> values)
    {
        _list = new List<int>(values);
    }

    // Перегрузка операции >> - удаление элемента на заданной позиции
    public static MyList operator >>(MyList myList, int position)
    {
        if (position >= 0 && position < myList._list.Count)
        {
            myList._list.RemoveAt(position);
        }
        return myList;
    }

    // Перегрузка операции + - добавление элемента на заданную позицию
    public static MyList operator +(MyList myList, (int position, int value) item)
    {
        if (item.position >= 0 && item.position <= myList._list.Count)
        {
            myList._list.Insert(item.position, item.value);
        }
        return myList;
    }

    // Перегрузка операции != - проверка на неравенство
    public static bool operator !=(MyList list1, MyList list2)
    {
        return !(list1 == list2);
    }

    // Перегрузка операции == - проверка на равенство
    public static bool operator ==(MyList list1, MyList list2)
    {
        return list1._list.SequenceEqual(list2._list);
    }

    // Переопределение методов Equals и GetHashCode для корректной работы с операторами == и !=
    public override bool Equals(object obj)
    {
        if (obj is MyList list)
        {
            return this == list;
        }
        return false;
    }

    public override int GetHashCode()
    {
        return _list.GetHashCode();
    }

    // Метод для добавления элемента в конец списка
    public void Add(int value)
    {
        _list.Add(value);
    }

    // Метод для удаления элемента на определенной позиции
    public void RemoveAt(int position)
    {
        if (position >= 0 && position < _list.Count)
        {
            _list.RemoveAt(position);
        }
    }

    // Метод для вывода списка
    public void Print()
    {
        Console.WriteLine(string.Join(", ", _list));
    }

    // Возвращение количества элементов в списке
    public int Count => _list.Count;

    // Возвращение суммы всех элементов списка
    public int Sum => _list.Sum();

    // Возвращение максимального элемента
    public int Max => _list.Max();

    // Возвращение минимального элемента
    public int Min => _list.Min();
}

// Вложенный объект Production
class Production
{
    public int Id { get; set; }
    public string Organization { get; set; }

    public Production(int id, string organization)
    {
        Id = id;
        Organization = organization;
    }
}

// Вложенный класс Developer
class Developer
{
    public string FullName { get; set; }
    public int Id { get; set; }
    public string Department { get; set; }

    public Developer(string fullName, int id, string department)
    {
        FullName = fullName;
        Id = id;
        Department = department;
    }
}

// Статический класс StatisticOperation для работы с MyList
static class StatisticOperation
{
    // Метод для подсчета суммы элементов списка
    public static int Sum(MyList list)
    {
        return list.Sum;
    }

    // Метод для вычисления разницы между максимальным и минимальным элементами
    public static int Difference(MyList list)
    {
        return list.Max - list.Min;
    }

    // Метод для подсчета количества элементов в списке
    public static int Count(MyList list)
    {
        return list.Count;
    }
}

// Методы расширения
static class ExtensionMethods
{
    // Метод расширения для поиска самого длинного слова в строке
    public static string LongestWord(this string str)
    {
        return str.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries)
                  .OrderByDescending(s => s.Length)
                  .FirstOrDefault();
    }

    // Метод расширения для удаления последнего элемента из списка
    public static void RemoveLast(this MyList list)
    {
        if (list.Count > 0)
        {
            list.RemoveAt(list.Count - 1);
        }
    }
}

// Тестирование программы
class Program
{
    static void Main()
    {
        // Создаем список
        MyList list1 = new MyList();
        list1.Add(1);
        list1.Add(2);
        list1.Add(3);
        list1.Print(); // Вывод: 1, 2, 3

        // Удаление элемента на позиции 1
        list1 = list1 >> 1;
        list1.Print(); // Вывод: 1, 3

        // Добавление элемента на позицию 1
        list1 = list1 + (1, 5);
        list1.Print(); // Вывод: 1, 5, 3

        // Создание второго списка для проверки неравенства
        MyList list2 = new MyList(new[] { 1, 5, 3 });
        Console.WriteLine(list1 != list2); // Вывод: False (списки равны)

        // Работа с методами расширения
        string testString = "This is an example string";
        Console.WriteLine(testString.LongestWord()); // Вывод: example

        // Удаление последнего элемента из списка
        list1.RemoveLast();
        list1.Print(); // Вывод: 1, 5
    }
}
