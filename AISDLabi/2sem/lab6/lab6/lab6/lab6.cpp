#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;


struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr) {
        this->ch = ch;
        this->freq = freq;
        this->left = left;
        this->right = right;
    }
};


struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Функция для обхода дерева Хаффмана
void encode(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // Если узел — лист, присваиваем код символу
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

void calculateFrequency(const string& text, unordered_map<char, int>& freq) {
    for (char ch : text) {
        freq[ch]++;
    }
}

// Построение дерева Хаффмана 
Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        int sum = left->freq + right->freq;
        pq.push(new Node('\0', sum, left, right));
    }

    return pq.top();
}

string decode(Node* root, const string& encodedStr) {
    string decodedStr;
    Node* current = root;

    for (char bit : encodedStr) {
        current = (bit == '0') ? current->left : current->right;

        // Если узел — лист, добавляем символ в результат
        if (!current->left && !current->right) {
            decodedStr += current->ch;
            current = root;
        }
    }

    return decodedStr;
}

int main() {
    setlocale(LC_ALL, ".1251");
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string text;
    cout << "Введите текст для кодирования: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Ошибка: текст не может быть пустым!" << endl;
        return 1;
    }

    // Шаг 1: Подсчет частоты символов
    unordered_map<char, int> freq;
    calculateFrequency(text, freq);

    // Шаг 2: Построение дерева Хаффмана
    Node* root = buildHuffmanTree(freq);

    // Шаг 3: Получение кодов символов
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    cout << "Частота символов:\n";
    for (auto pair : freq) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    cout << "\nКоды символов:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << ": " << pair.second << "\n";
    }

    // Шаг 4: Кодирование текста
    string encodedStr;
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }

    cout << "\nЗакодированная строка:\n" << encodedStr << endl;

    // Шаг 5: Декодирование строки (для проверки)
    string decodedStr = decode(root, encodedStr);
    cout << "\nДекодированная строка:\n" << decodedStr << endl;

    return 0;
}

