#include "GRB.h"  // структуры для работы с грамматикой Грейбаха.
#include "Rules.h" // содержащий правила.
#include "string.h" 

namespace GRB 
{
    Rule::Chain::Chain(short psize, GRBALPHABET s, ...) // Конструктор Chain (цепочки) класса Rule. Принимает количество элементов и переменное число аргументов.
    {
        this->nt = new GRBALPHABET[this->size = psize]; // Выделяем память для массива nt, в который будем сохранять цепочку символов.

        int* ptr = (int*)&s; // Создаем указатель на первый элемент переданных аргументов.
        for (int i = 0; i < psize; i++) // Цикл по количеству элементов в цепочке.
            this->nt[i] = (short)ptr[i]; // Присваиваем элементы массива nt, используя указатель ptr.
    }

    Rule::Rule(GRBALPHABET pnn, int iderroe, short psize, Chain c, ...) // Конструктор класса Rule. Принимает начальный символ правила, код ошибки, размер и переменное количество цепочек.
    {
        this->nn = pnn; // Сохраняем начальный символ (нетерминал).
        this->iderror = iderroe; // Сохраняем код ошибки.
        this->chains = new Chain[this->size = psize]; // Выделяем память для массива цепочек и задаём их размер.
        Chain* ptr = &c; // Создаем указатель на первую цепочку.
        for (int i = 0; i < psize; i++) // Цикл по количеству цепочек.
            this->chains[i] = ptr[i]; // Копируем каждую цепочку в массив chains.
    }

    Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...) // Конструктор класса Greibach. Принимает начальный символ, символ дна стека, размер и переменное число правил.
    {
        this->startN = pstartN; // Сохраняем начальный символ грамматики.
        this->stbottomT = pstbottomT; // Сохраняем символ дна стека.
        this->rules = new Rule[this->size = psize]; // Выделяем память для массива правил и задаём их размер.
        Rule* ptr = &r; // Создаем указатель на первое правило.
        for (int i = 0; i < psize; i++) // Цикл по количеству правил.
            rules[i] = ptr[i]; // Копируем каждое правило в массив rules.
    }

    short Greibach::getRule(GRBALPHABET pnn, Rule& prule) // Метод для получения правила по заданному символу.
    {
        short rc = -1, k = 0; // Инициализируем переменные: rc для результата и k для итерации.
        while (k < this->size && rules[k].nn != pnn) // Поиск правила с нетерминалом pnn.
            k++;
        if (k < this->size) // Если правило найдено:
            prule = rules[rc = k]; // Присваиваем найденное правило и индекс.
        return rc; // Возвращаем индекс найденного правила или -1, если не найдено.
    }

    Rule Greibach::getRule(short n) // Перегруженный метод для получения правила по индексу.
    {
        Rule rc;
        if (n < this->size) // Если индекс в пределах массива:
            rc = rules[n]; // Присваиваем правило с этим индексом.
        return rc; // Возвращаем правило (пустое, если не найдено).
    }

    char* Rule::getCRule(char* b, short nchain) // Метод для получения строки, представляющей правило в виде символов.
    {
        char buf[200]; // Временный буфер для цепочки.
        b[0] = Chain::alphabet_to_char(this->nn); // Преобразуем нетерминал nn в символ и сохраняем в b.
        b[1] = '-';
        b[2] = '>';
        b[3] = 0x00; // Завершаем строку.
        this->chains[nchain].getCChain(buf); // Получаем строковое представление цепочки.
        strcat_s(b, sizeof(buf) + 5, buf); // Конкатенируем строку правила с буфером цепочки.

        return b; // Возвращаем итоговую строку.
    }

    short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) // Метод для поиска следующей цепочки по заданному символу.
    {
        short rc = -1; // Инициализируем переменную для результата.

        while (j < this->size && this->chains[j].nt[0] != t) // Поиск цепочки, которая начинается с символа t.
            j++;

        rc = (j < this->size ? j : -1); // Если цепочка найдена, присваиваем индекс, иначе -1.
        if (rc >= 0) // Если цепочка найдена:
            pchain = chains[rc]; // Присваиваем найденную цепочку.
        return rc; // Возвращаем индекс найденной цепочки или -1.
    }

    char* Rule::Chain::getCChain(char* b) // Метод для получения строкового представления цепочки.
    {
        for (int i = 0; i < this->size; i++) // Проходим по каждому символу в цепочке.
            b[i] = Chain::alphabet_to_char(this->nt[i]); // Преобразуем символ и сохраняем в b.
        b[this->size] = 0; // Завершаем строку.
        return b; // Возвращаем строку.
    }

    Greibach getGreibach() // Функция для получения объекта Greibach.
    {
        return greibach; // Возвращаем глобальный объект greibach.
    }
}
