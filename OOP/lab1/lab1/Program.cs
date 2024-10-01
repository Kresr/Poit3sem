using System;
using System.Text;

class Program
{
    static void Main()
    {
        //task 1-4
        Console.Write("  \n");
        Console.Write("  \n");
        task1();
        Console.Write("  \n");
        Console.Write("  \n");
        task2();
        Console.Write("  \n");
        Console.Write("  \n");
        task3();
        Console.Write("  \n");
        Console.Write("  \n");
        task4();

        //task5
        Console.Write("  \n");
        Console.Write("  \n");

        int[] numbers = { 1, 3, 5, 7, 9 };
        string text = "Hello";
        var result = ProcessData(numbers, text);
        Console.WriteLine($"Максимум: {result.Max}, Минимум: {result.Min}, Сумма: {result.Sum}, Первая буква: {result.FirstLetter}");


        //task 6
        Console.Write("  \n");
        Console.Write("  \n");
        CheckedFunction();
        UncheckedFunction();

        Console.WriteLine("Нажмите любую клавишу для выхода...");
        Console.ReadKey(); // Или Console.ReadLine();
    }

    static (int Max, int Min, int Sum, char FirstLetter) ProcessData(int[] array, string str)
    {
        // 5
        // Локальная функция
        (int, int, int, char) Calculate()
        {
            int max = array[0];
            int min = array[0];
            int sum = 0;

            foreach (var number in array)
            {
                if (number > max) max = number;
                if (number < min) min = number;
                sum += number;
            }

            char firstLetter = str.Length > 0 ? str[0] : '\0'; // Проверка на пустую строку
            return (max, min, sum, firstLetter);
        }

        return Calculate();
    }
    static void CheckedFunction()
    {
        // Локальная функция с блоком checked
        try
        {
            checked
            {
                int maxInt = int.MaxValue;
                int result = maxInt + 1; // Переполнение
                Console.WriteLine($"Result in CheckedFunction: {result}");
            }
        }
        catch (OverflowException e)
        {
            Console.WriteLine($"CheckedFunction: {e.Message}"); // Сообщение об ошибке
        }
    }

    static void UncheckedFunction()
    {
        // Локальная функция с блоком unchecked
        unchecked
        {
            int maxInt = int.MaxValue;
            int result = maxInt + 1; // Переполнение
            Console.WriteLine($"Result in UncheckedFunction: {result}"); // Обрезка
        }
    }

    static void task1()
    {
        bool boolVar = true;
        Console.WriteLine($"bool: {boolVar}");
        byte byteVar = 2;
        Console.WriteLine($"byte: {byteVar}");
        sbyte sbyteVar = -1;
        Console.WriteLine($"sbyte: {sbyteVar}");
        char charVar = 'A';
        Console.WriteLine($"char: {charVar}");
        decimal decimalVar = 59.9m;
        Console.WriteLine($"decimal: {decimalVar}");
        double doubleVar = 3.213;
        Console.WriteLine($"double: {doubleVar}");
        float floatVar = 2.52f;
        Console.WriteLine($"float: {floatVar}");
        int intVar = 412;
        Console.WriteLine($"int: {intVar}");
        long longVar = 12345;
        Console.WriteLine($"long: {longVar}");
        ulong ulongVar = 120;
        Console.WriteLine($"ulong: {ulongVar}");
        short shortVar = -68;
        Console.WriteLine($"short: {shortVar}");
        ushort ushortVar = 65;
        Console.WriteLine($"ushort: {ushortVar}");


        double implicitDouble = intVar;
        int explicitInt = (int)doubleVar;

        decimal implicitDecimal = 20.5M;
        long implicitLong = 100000;
        float implicitFloat = 10;

        sbyte explicitSbyte = (sbyte)intVar;
        short explicitShort = (short)intVar;
        int explicitIntFromLong = (int)longVar;
        ulong explicitUlong = (ulong)longVar;
        byte explicitByte = (byte)byteVar;


        string numberString = "312341";
        int convertedInt = Convert.ToInt32(numberString);
        Console.WriteLine($"Converted int: {convertedInt}");


        int packedValue = 22;
        object boxedValue = packedValue;
        int unboxedValue = (int)boxedValue;
        Console.WriteLine($"Unboxed val: {unboxedValue}");


        var implicitlyTypedVar = "Hello !!!!";
        Console.WriteLine($"Implicitly typed variable: {implicitlyTypedVar}");


        int? nullableInt = null;
        nullableInt = 10;
        Console.WriteLine($"Nullable variable: {nullableInt}");


        var varVariable = 42;
    }

    static void task2()
    {
        string str1 = "Hello";
        string str2 = "Hello";
        string str3 = "World";

        bool areEqual = str1 == str2;
        bool areDifferent = str1 == str3;

        //--------

        string strA = "Привет";
        string strB = "Мир";
        string strC = "Как дела";

        string concatenated = strA + " " + strB;
        string copiedString = string.Copy(strA);
        string substring = strC.Substring(0, 4);
        string[] words = strC.Split(' ');
        string insertedString = strC.Insert(4, "все ");
        string modifiedString = strC.Remove(4, 4);
        string interpolated = $"Строка: {strA}, {strB}, {strC}";

        //---------

        string emptyString = "";
        string nullString = null;

        bool isEmpty = string.IsNullOrEmpty(emptyString);
        bool isNull = string.IsNullOrEmpty(nullString);
        string defaultString = emptyString ?? "Пустая строка";

        //---------        

        StringBuilder sb = new StringBuilder("Hello World");
        sb.Remove(5, 5);
        sb.Insert(0, "Greetings, ");
        sb.Append("!!!");
        string resultString = sb.ToString();
    }

    static void task3()
    {
        int[,] matrix = {
            { 1, 2, 3 },
            { 4, 5, 6 },
            { 7, 8, 9 }
        };

        for (int i = 0; i < matrix.GetLength(0); i++)
        {
            for (int j = 0; j < matrix.GetLength(1); j++)
            {
                Console.Write(matrix[i, j] + "\t");
            }
            Console.WriteLine();
        }

        //-----------

        string[] stringArray = { "Apple", "Banana", "Cherry" };

        Console.WriteLine("Содержимое массива:");
        foreach (var item in stringArray)
        {
            Console.WriteLine(item);
        }
        Console.WriteLine("Длина массива: " + stringArray.Length);

        Console.Write("Введите индекс для изменения: ");
        int index = int.Parse(Console.ReadLine());
        Console.Write("Введите новое значение: ");
        string newValue = Console.ReadLine();

        if (index >= 0 && index < stringArray.Length)
        {
            stringArray[index] = newValue;
        }

        //------------

        double[][] jaggedArray = new double[3][];
        jaggedArray[0] = new double[2];
        jaggedArray[1] = new double[3];
        jaggedArray[2] = new double[4];

        for (int i = 0; i < jaggedArray.Length; i++)
        {
            Console.WriteLine($"Введите значения для строки {i + 1}:");
            for (int j = 0; j < jaggedArray[i].Length; j++)
            {
                jaggedArray[i][j] = double.Parse(Console.ReadLine());
            }
        }

        //-------------

        var array = new[] { 1, 2, 3, 4 };
        var message = "Hello, World!";
    }

    static void task4()
    {
        var tuple = (12, "Hello", 'A', "World", 123456789UL);

        //------

        Console.WriteLine($"Кортеж: {tuple}");
        Console.WriteLine($"элемент 1: {tuple.Item1}");
        Console.WriteLine($"элемент 3: {tuple.Item3}");
        Console.WriteLine($"элемент 4: {tuple.Item4}");

        //------

        (int number, string greeting, char initial, string place, ulong bigNumber) = tuple;

        Console.WriteLine($"Число: {number}, Приветствие: {greeting}, Инициал: {initial}, Место: {place}, Большое число: {bigNumber}");

        var (num, greet, _, loc, big) = tuple;
        Console.WriteLine($"Число: {num}, Приветствие: {greet}, Место: {loc}, Большое число: {big}");
        var tuple1 = (13, "Hello", 'A', "World", 19UL);
        var tuple2 = (15, "Hello", 'A', "World", 89UL);
        var tuple3 = (26, "Hello", 'B', "World", 921UL);

        Console.WriteLine(tuple1 == tuple2);
        Console.WriteLine(tuple1 == tuple3);
    }
}
