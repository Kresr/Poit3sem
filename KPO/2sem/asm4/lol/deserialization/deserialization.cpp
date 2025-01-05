#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

// Пример структуры
struct MyStruct {
    int id;
    float value;
};

// Типы данных с кодами
#define TYPE_BOOL 0x01
#define TYPE_CHAR_ARRAY 0x02
#define TYPE_STRUCT 0x03
#define TYPE_INT_ARRAY 0x04

// Десериализация данных
void deserialize(const std::string& filename, bool& boolean, char char_array[], MyStruct& my_struct, std::vector<int>& int_array) {
    std::ifstream infile(filename, std::ios::binary);
    if (!infile.is_open()) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    while (infile.peek() != EOF) {
        // Читаем тип
        char type = infile.get();

        if (type == TYPE_BOOL) {
            boolean = infile.get();
        }
        else if (type == TYPE_CHAR_ARRAY) {
            char len = infile.get();
            infile.read(char_array, len);
        }
        else if (type == TYPE_STRUCT) {
            infile.read(reinterpret_cast<char*>(&my_struct), sizeof(MyStruct));
        }
        else if (type == TYPE_INT_ARRAY) {
            size_t array_size;
            infile.read(reinterpret_cast<char*>(&array_size), sizeof(size_t));
            int_array.resize(array_size);
            infile.read(reinterpret_cast<char*>(int_array.data()), array_size * sizeof(int));
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

    // Генерация данных для строки (0x02)
    asmfile << "CHAR_ARRAY DB ";
    for (size_t i = 0; i < len; ++i) {
        asmfile << "'" << char_array[i] << "'" << (i < len - 1 ? ", " : "");
    }
    asmfile << ", 0\n";

    // Генерация данных для boolean (0x01)
    asmfile << "BOOLEAN DB " << (boolean ? "1" : "0") << "\n";

    // Генерация данных для структуры (0x03)
    asmfile << "STRUCT_ID DD " << my_struct.id << "\n";
    asmfile << "STRUCT_VALUE DD " << my_struct.value << "\n";

    // Генерация данных для массива целых чисел (0x04)
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
