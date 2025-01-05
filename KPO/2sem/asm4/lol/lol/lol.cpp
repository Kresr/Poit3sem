#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

// Типы данных
#define TYPE_CHAR_ARRAY 0x02
#define TYPE_BOOL 0x01
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

    // Сериализуем массив char
    outfile.put(TYPE_CHAR_ARRAY);
    outfile.put(static_cast<char>(len)); // длина массива
    outfile.write(char_array, len);

    // Сериализуем bool
    outfile.put(TYPE_BOOL);
    outfile.put(boolean ? 1 : 0); // значение

    // Сериализуем структуру
    outfile.put(TYPE_STRUCT);
    outfile.write(reinterpret_cast<const char*>(&my_struct), sizeof(MyStruct));

    // Сериализуем массив целых чисел
    outfile.put(TYPE_INT_ARRAY);
    size_t array_size = int_array.size();
    outfile.write(reinterpret_cast<const char*>(&array_size), sizeof(size_t));
    outfile.write(reinterpret_cast<const char*>(int_array.data()), array_size * sizeof(int));

    outfile.close();
}

// Десериализация данных
void deserialize(const std::string& filename) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    while (infile.peek() != EOF) {
        // Читаем тип
        char type = infile.get();

        if (type == TYPE_CHAR_ARRAY) {
            char len = infile.get();
            std::vector<char> char_array(len);
            infile.read(char_array.data(), len);
            std::cout << "Char Array: " << std::string(char_array.begin(), char_array.end()) << std::endl;
        }
        else if (type == TYPE_BOOL) {
            char boolean = infile.get();
            std::cout << "Boolean: " << (boolean ? "true" : "false") << std::endl;
        }
        else if (type == TYPE_STRUCT) {
            MyStruct my_struct;
            infile.read(reinterpret_cast<char*>(&my_struct), sizeof(MyStruct));
            std::cout << "Struct - ID: " << my_struct.id << ", Value: " << my_struct.value << std::endl;
        }
        else if (type == TYPE_INT_ARRAY) {
            size_t array_size;
            infile.read(reinterpret_cast<char*>(&array_size), sizeof(size_t));
            std::vector<int> int_array(array_size);
            infile.read(reinterpret_cast<char*>(int_array.data()), array_size * sizeof(int));
            std::cout << "Int Array: ";
            for (int num : int_array) {
                std::cout << num << " ";
            }
            std::cout << std::endl;
        }
    }

    infile.close();
}

// Генерация ассемблерного кода
void generate_asm(const std::string& filename, const char char_array[], size_t len, bool boolean, const MyStruct& my_struct, const std::vector<int>& int_array) {
    std::ofstream asmfile(filename);
    if (!asmfile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    asmfile << ".586P\n";
    asmfile << ".MODEL FLAT, STDCALL\n";
    asmfile << "includelib kernel32.lib\n";
    asmfile << "ExitProcess PROTO : DWORD\n";
    asmfile << "MessageBoxA PROTO : DWORD, : DWORD, : DWORD, : DWORD\n";
    asmfile << ".STACK 4096\n";
    asmfile << ".DATA\n";
    asmfile << "MB_OK EQU 0\n";
    asmfile << "STR1 DB \"MessageBox Example\", 0\n";
    asmfile << "HW DD ?\n";

    asmfile << "CHAR_ARRAY DB ";
    for (size_t i = 0; i < len; ++i) {
        asmfile << "'" << char_array[i] << "'" << (i < len - 1 ? ", " : "");
    }
    asmfile << ", 0\n";

    asmfile << "BOOLEAN DB " << (boolean ? "1" : "0") << "\n";

    asmfile << "STRUCT_ID DD " << my_struct.id << "\n";
    asmfile << "STRUCT_VALUE DD " << my_struct.value << "\n";

    asmfile << "INT_ARRAY DD ";
    for (size_t i = 0; i < int_array.size(); ++i) {
        asmfile << int_array[i] << (i < int_array.size() - 1 ? ", " : "");
    }
    asmfile << "\n";

    asmfile << ".CODE\n";
    asmfile << "main PROC\n";
    asmfile << "    INVOKE MessageBoxA, HW, OFFSET CHAR_ARRAY, OFFSET STR1, MB_OK\n";
    asmfile << "    push 0\n";
    asmfile << "    call ExitProcess\n";
    asmfile << "main ENDP\n";
    asmfile << "end main\n";

    asmfile.close();
}

int main() {
    const char char_array[10] = "stas";
    bool boolean = false;
    MyStruct my_struct = { 42, 3.14f };
    std::vector<int> int_array = { 1, 2, 3, 4, 5 };

    // Сериализация
    serialize("data.bin", char_array, strlen(char_array), boolean, my_struct, int_array);

    // Десериализация
    deserialize("data.bin");

    // Генерация ассемблерного кода
    generate_asm("output.asm", char_array, strlen(char_array), boolean, my_struct, int_array);

    std::cout << "Assembly code has been generated and saved to output.asm." << std::endl;

    return 0;
}
