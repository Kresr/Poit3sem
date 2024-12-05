using System;
using System.Diagnostics;
using System.IO;

namespace ExceptionHandling
{
    // Пользовательские исключения
    public class InvalidDataException : Exception
    {
        public InvalidDataException(string message) : base(message) { }
    }

    public class FileReadException : Exception
    {
        public FileReadException(string message) : base(message) { }
    }

    public class DivideByZeroCustomException : Exception
    {
        public DivideByZeroCustomException(string message) : base(message) { }
    }

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // Исключение: неверные данные
                int[] array = new int[5];
                array[10] = 1;  // IndexOutOfRangeException

                // Исключение: деление на ноль
                int x = 0;
                if (x == 0) throw new DivideByZeroCustomException("Ошибка деления на ноль");

                // Исключение: чтение файла
                ReadFile("nonexistent.txt");

                // Проверка через Assert
                Debug.Assert(array != null, "Массив не должен быть null");
            }
            catch (IndexOutOfRangeException ex)
            {
                Console.WriteLine($"Исключение: {ex.Message}");
                throw;  // Проброс исключения
            }
            catch (DivideByZeroCustomException ex)
            {
                Console.WriteLine($"Исключение: {ex.Message}");
            }
            catch (FileReadException ex)
            {
                Console.WriteLine($"Исключение: {ex.Message}");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Общее исключение: {ex.Message}");
            }
            finally
            {
                Console.WriteLine("Завершение обработки исключений");
            }
        }

        static void ReadFile(string filePath)
        {
            if (!File.Exists(filePath))
                throw new FileReadException($"Файл {filePath} не найден");
        }
    }
}


