#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

// Типы данных с кодами
#define TYPE_BOOL 0x01
#define TYPE_CHAR_ARRAY 0x02
#define TYPE_STRUCT 0x03
#define TYPE_INT_ARRAY 0x04

// Пример структуры
struct MyStruct {
    int id;
    float value;
};

// Сериализация данных
void serialize(const std::string& filename, const char char_array[], size_t len, bool boolean, const MyStruct& my_struct, const std::vector<int>& int_array) {
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    // Сериализуем bool (0x01)
    outfile.put(TYPE_BOOL);
    outfile.put(boolean ? 1 : 0); // значение

    // Сериализуем массив char (0x02)
    outfile.put(TYPE_CHAR_ARRAY);
    outfile.put(static_cast<char>(len)); // длина массива
    outfile.write(char_array, len);

    // Сериализуем структуру (0x03)
    outfile.put(TYPE_STRUCT);
    outfile.write(reinterpret_cast<const char*>(&my_struct), sizeof(MyStruct));

    // Сериализуем массив целых чисел (0x04)
    outfile.put(TYPE_INT_ARRAY);
    size_t array_size = int_array.size();
    outfile.write(reinterpret_cast<const char*>(&array_size), sizeof(size_t));
    outfile.write(reinterpret_cast<const char*>(int_array.data()), array_size * sizeof(int));

    outfile.close();
}
