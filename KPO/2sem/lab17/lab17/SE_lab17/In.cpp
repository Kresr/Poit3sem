#include "stdafx.h"
using namespace std;

namespace In
{
    void removeExtraSpaces(std::string& input, int& removedSpacesCount)
    {
        bool insideQuotes = false;

        for (size_t i = 0; i < input.length(); ++i)
        {
            if (input[i] == '\'') {
                insideQuotes = !insideQuotes;
            }
            if (!insideQuotes && input[i] == ' ')
            {
                if (i == 0 || i == input.length() - 1)
                {
                    input.erase(i, 1);
                    removedSpacesCount++; // считаем удаленные пробелы
                    --i; // корректируем индекс, так как удалили символ
                }
                size_t spacesToRemove = 0;
                while (i + spacesToRemove < input.length() && input[i + spacesToRemove] == ' ')
                {
                    ++spacesToRemove;
                }
                if (spacesToRemove > 1)
                {
                    input.erase(i + 1, spacesToRemove - 1);
                    removedSpacesCount += spacesToRemove - 1; // считаем удаленные пробелы
                }
            }
        }
    }

    void removeSpacesAroundOperators(std::string& input, int& removedSpacesCount)
    {
        const std::string operators = ";,}{()=+-/*";

        for (size_t i = 0; i < input.length(); ++i)
        {
            if (operators.find(input[i]) != std::string::npos)
            {
                // Удаляем пробелы перед символом
                while (i > 0 && std::isspace(input[i - 1]))
                {
                    input.erase(i - 1, 1);
                    removedSpacesCount++; // считаем удаленные пробелы
                    --i;
                }

                // Удаляем пробелы после символа
                while (i + 1 < input.length() && std::isspace(input[i + 1]))
                {
                    input.erase(i + 1, 1);
                    removedSpacesCount++; // считаем удаленные пробелы
                }
            }
        }
    }

    IN getin(wchar_t infile[])
    {
        ifstream fin;
        char* outFile = new char[wcslen(infile) + 1];
        wcstombs_s(NULL, outFile, wcslen(infile) + 1, infile, wcslen(infile) + 1);
        fin.open(infile);
        if (fin.bad())
        {
            throw ERROR_THROW(116);
        }
        if (!fin.is_open())
        {
            throw ERROR_THROW(110);
        }
        IN resultIn;
        resultIn.size = 0;
        resultIn.lines = 0;
        int position = 0;
        int ch;
        std::string currentLine;
        std::string buffer;
        int totalRemovedSpaces = 0; // добавляем переменную для подсчета всех удаленных пробелов

        while (std::getline(fin, buffer))
        {
            resultIn.lines++;
            for (int i = 0; i < buffer.length(); i++)
            {
                ch = buffer[i];

                if (ch == fin.eof())
                {
                    break;
                }

                switch (resultIn.code[(unsigned char)ch])
                {
                case IN::F:
                {
                    resultIn.text.push_back(currentLine);
                    throw ERROR_THROW_IN(111, resultIn.lines, ++position, buffer, resultIn.text);
                    break;
                }
                case IN::I:
                {
                    resultIn.ignor++;
                    position++;
                    break;
                }
                case IN::T:
                {

                    currentLine += ch;
                    position++;
                    resultIn.size++;
                    break;
                }
                default:
                {
                    currentLine += resultIn.code[(unsigned char)ch];
                    resultIn.size++;
                    position++;
                    break;
                }
                }
            }

            if (!currentLine.empty())
            {
                resultIn.size++;
                position++;
                position = 0;
                currentLine += resultIn.code[IN_CODE_ENDL];

                int removedSpaces = 0;
                removeExtraSpaces(currentLine, removedSpaces);
                totalRemovedSpaces += removedSpaces;

                removedSpaces = 0;
                removeSpacesAroundOperators(currentLine, removedSpaces);
                totalRemovedSpaces += removedSpaces;

                resultIn.text.push_back(currentLine);
                currentLine.clear();
            }
        }

        resultIn.removedSpaces = totalRemovedSpaces; // сохраняем итоговое количество удаленных пробелов
        fin.close();
        return resultIn;
    }
}

