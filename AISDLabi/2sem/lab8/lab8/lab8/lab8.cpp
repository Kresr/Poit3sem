#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    string name; 
    int weight;  
    int value;   
};

void knapsack(int capacity, Item* items, int numItems) {

    int** dp = new int* [numItems + 1];
    for (int i = 0; i <= numItems; ++i) {
        dp[i] = new int[capacity + 1];
    }


    for (int i = 0; i <= numItems; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "Максимальная стоимость: " << dp[numItems][capacity] << endl;
    cout << "Предметы в рюкзаке:" << endl;


    int w = capacity;
    for (int i = numItems; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "  - " << items[i - 1].name << " (вес: " << items[i - 1].weight << ", стоимость: " << items[i - 1].value << ")" << endl;
            w -= items[i - 1].weight;
        }
    }

    for (int i = 0; i <= numItems; ++i) {
        delete[] dp[i];
    }
    delete[] dp;
}

int main() {
    setlocale(LC_ALL, "RUSSIAN"); 

    int capacity;
    cout << "Введите вместимость рюкзака: ";
    cin >> capacity;

    int numItems;
    cout << "Введите количество товаров: ";
    cin >> numItems;

    Item* items = new Item[numItems];


    for (int i = 0; i < numItems; ++i) {
        cout << "Товар #" << i + 1 << ":" << endl;
        cin.ignore(); 
        cout << "  Название: ";
        getline(cin, items[i].name); 
        cout << "  Вес: ";
        cin >> items[i].weight;
        cout << "  Стоимость: ";
        cin >> items[i].value;
    }

 
    knapsack(capacity, items, numItems);

    delete[] items;

    return 0;
}
