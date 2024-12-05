using System;
using System.Collections.Generic;
using System.Linq;

namespace GameSimulation
{
    // Класс, представляющий игрового персонажа
    public class GameCharacter
    {
        public string Name { get; private set; }
        public int Health { get; set; }

        public event Action<int> OnAttack;
        public event Action<int> OnHeal;

        public GameCharacter(string name, int initialHealth)
        {
            Name = name;
            Health = initialHealth;
        }

        public void Attack(int damage)
        {
            OnAttack?.Invoke(damage);
            Health -= damage;
            Console.WriteLine($"{Name} получил {damage} урона, текущее здоровье: {Health}");
        }

        public void Heal(int amount)
        {
            OnHeal?.Invoke(amount);
            Health += amount;
            Console.WriteLine($"{Name} восстановил {amount} здоровья, текущее здоровье: {Health}");
        }
    }

    // Класс, управляющий событиями игры
    public class Game
    {
        public void Subscribe(GameCharacter character)
        {
            character.OnAttack += damage =>
            {
                Console.WriteLine($"{character.Name} был атакован на {damage}!");
                if (character.Health <= 0)
                {
                    Console.WriteLine($"{character.Name} погиб!");
                }
            };

            character.OnHeal += amount =>
            {
                Console.WriteLine($"{character.Name} был исцелен на {amount}!");
            };
        }
    }

    // Класс для обработки строк
    public static class StringProcessor
    {
        public static string RemovePunctuation(string input) => new string(input.Where(c => !char.IsPunctuation(c)).ToArray());

        public static string AddSymbol(string input, char symbol) => input + symbol;

        public static string ReplaceWithUppercase(string input) => input.ToUpper();

        public static string RemoveExtraSpaces(string input) => string.Join(" ", input.Split(new[] { ' ' }, StringSplitOptions.RemoveEmptyEntries));

        public static string ReplaceSubstring(string input, string oldValue, string newValue) => input.Replace(oldValue, newValue);
    }

    class Program
    {
        static void Main(string[] args)
        {
            // Создание игровых объектов
            var character1 = new GameCharacter("Warrior", 100);
            var character2 = new GameCharacter("Mage", 80);

            // Создание игры и подписка на события
            var game = new Game();
            game.Subscribe(character1);
            game.Subscribe(character2);

            // Симуляция событий
            character1.Attack(30);
            character2.Heal(20);
            character1.Attack(80); // Warrior погибает

            // Обработка строки
            string input = "Hello,   world! Welcome to  C# programming.";
            Console.WriteLine($"Исходная строка: {input}");
            Action<string> processString = str =>
            {
                str = StringProcessor.RemovePunctuation(str);
                str = StringProcessor.RemoveExtraSpaces(str);
                str = StringProcessor.AddSymbol(str, '!');
                str = StringProcessor.ReplaceWithUppercase(str);
                str = StringProcessor.ReplaceSubstring(str, "WORLD", "UNIVERSE");
                Console.WriteLine($"Обработанная строка: {str}");
            };
            processString(input);
        }
    }
}

