#include <iostream>
#include <string>

using namespace std;

// Структура "Студент"
struct Student {
    string full_name;      // Псевдоним: ФИО
    int age;               // Псевдоним: Возраст
    char gender;           // Псевдоним: Пол
    string specialization; // Псевдоним: Специальность
    int course;            // Псевдоним: Курс
    string group;          // Псевдоним: Группа
    float average_grade;   // Псевдоним: Средний балл
    int health_absences;   // Псевдоним: Количество пропусков по болезни

    // Перегрузка оператора сравнения по среднему баллу
    bool operator<(const Student& other) const {
        return average_grade < other.average_grade;
    }

    // Перегрузка оператора равенства
    bool operator==(const Student& other) const {
        return average_grade == other.average_grade;
    }

    // Перегрузка оператора неравенства
    bool operator!=(const Student& other) const {
        return !(*this == other);
    }
};

// Операция для вывода информации о студенте
ostream& operator<<(ostream& os, const Student& student) {
    os << "ФИО: " << student.full_name << endl;
    os << "Возраст: " << student.age << endl;
    os << "Пол: " << student.gender << endl;
    os << "Специальность: " << student.specialization << endl;
    os << "Курс: " << student.course << endl;
    os << "Группа: " << student.group << endl;
    os << "Средний балл: " << student.average_grade << endl;
    os << "Количество пропусков по болезни: " << student.health_absences << endl;

    return os;
}

int main() {
    setlocale(LC_ALL, "RUS");
    Student student1 = { "Иванов Иван Иванович", 20, 'М', "Информатика", 2, "ИНФ-202", 4.5, 2 };
    Student student2 = { "Петрова Анна Сергеевна", 21, 'Ж', "Физика", 3, "ФИЗ-301", 4.8, 0 };
    Student student3 = { "Сидоров Петр Петрович", 22, 'М', "Информатика", 2, "ИНФ-201", 4.5, 1 };

    cout << "Студент 1:\n" << student1 << endl;
    cout << "Студент 2:\n" << student2 << endl;
    cout << "Студент 3:\n" << student3 << endl;

    // Сравнение студентов по среднему баллу
    if (student1 < student2) {
        cout << "Студент 1 имеет меньший средний балл чем Студент 2." << endl;
    }
    else {
        cout << "Студент 2 имеет меньший средний балл чем Студент 1." << endl;
    }

    // Проверка на равенство средних баллов
    if (student1 == student3) {
        cout << "Студент 1 и Студент 3 имеют равные средние баллы." << endl;
    }
    else {
        cout << "Студент 1 и Студент 3 имеют разные средние баллы." << endl;
    }

    // Проверка на неравенство средних баллов
    if (student2 != student3) {
        cout << "Студент 2 и Студент 3 имеют разные средние баллы." << endl;
    }
    else {
        cout << "Студент 2 и Студент 3 имеют равные средние баллы." << endl;
    }

    return 0;
}


