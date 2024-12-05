//1.Создайте объекты (Object) для фигур, представленных на картинке. Обратите внимание, фигуры имеют одинаковые параметры, следовательно одни объекты могут наследовать от других.
// Базовый класс Shape
class Shape {
    constructor(color) {
        this.color = color;
    }

    // Метод для вывода информации о фигуре
    getInfo() {
        return `Цвет: ${this.color}`;
    }
}

// Класс Square, наследуется от Shape
class Square extends Shape {
    constructor(color, sideLength) {
        super(color);
        this.sideLength = sideLength;
    }

    getInfo() {
        return `Фигура: Квадрат, ${super.getInfo()}, Сторона: ${this.sideLength}`;
    }
}

// Класс Circle, наследуется от Shape
class Circle extends Shape {
    constructor(color, radius) {
        super(color);
        this.radius = radius;
    }

    getInfo() {
        return `Фигура: Круг, ${super.getInfo()}, Радиус: ${this.radius}`;
    }
}

// Класс Triangle, наследуется от Shape
class Triangle extends Shape {
    constructor(color, sideLength, subTriangles) {
        super(color);
        this.sideLength = sideLength;
        this.subTriangles = subTriangles; // количество вложенных треугольников
    }

    getInfo() {
        return `Фигура: Треугольник, ${super.getInfo()}, Сторона: ${this.sideLength}, Вложенные треугольники: ${this.subTriangles}`;
    }
}

// Создание объектов на основе изображённых фигур
const yellowSquare = new Square("Yellow", 50); // Большой жёлтый квадрат
const smallYellowSquare = new Square("Yellow", 25); // Маленький жёлтый квадрат

const whiteCircle = new Circle("White", 50); // Белый круг
const greenCircle = new Circle("Green", 50); // Зелёный круг

const simpleTriangle = new Triangle("White", 50, 1); // Белый треугольник с одной линией
const complexTriangle = new Triangle("White", 50, 3); // Белый треугольник с двумя вложенными линиями


// 1. Получить свойства, которые отличают фигуру "зеленый круг"
const greenCircleProperties = Object.keys(greenCircle).filter(
    prop => greenCircle.hasOwnProperty(prop)
);
console.log("Свойства зеленого круга:", greenCircleProperties);

// 2. Получить свойства, которые описывают фигуру "треугольник с тремя линиями"
const complexTriangleProperties = Object.keys(complexTriangle).filter(
    prop => complexTriangle.hasOwnProperty(prop)
);
console.log("Свойства треугольника с тремя линиями:", complexTriangleProperties);

// 3. Проверить, есть ли у фигуры "маленький квадрат" собственное свойство, которое определяет цвет фигуры
const hasOwnColorProperty = smallYellowSquare.hasOwnProperty("color");
console.log("У маленького квадрата есть собственное свойство color:", hasOwnColorProperty);

// Также можно просто проверить значение свойства color у маленького квадрата
const smallSquareColor = smallYellowSquare.color;
console.log("Цвет маленького квадрата:", smallSquareColor);

// Вывод информации о фигурах
console.log(yellowSquare.getInfo());
console.log(smallYellowSquare.getInfo());
console.log(whiteCircle.getInfo());
console.log(greenCircle.getInfo());
console.log(simpleTriangle.getInfo());
console.log(complexTriangle.getInfo());


//С помощью методов JS получите свойства, которые отличают фигуру «зеленый круг»; свойства, которые описывают фигуру «треугольник с тремя линиями»; есть ли у фигуры «маленький квадрат» собственное свойство, которое определяет цвет фигуры.



//2.Реализуйте иерархию классов:

// Human: содержит поля Имя, Фамилия, Возраст, Адрес.Методы, позволяющие изменить значения для возраста и адреса.
class Human {
    _name = "aboba"
    #sername = "nyya"
    _age = 27
    #adress = "35 20"

    constructor(name) {
        this._name = name
    }

    changeAge(newAge) {
        if (newAge > 0) {
            this._age = newAge
        }
        else {
            console.log("Ошибка, возраст не может быть отрицательным")
        }
    }
    changeName(newName) {
        if (newName != "") {
            this._name = newName
        }
        else {
            console.log("Ошибка, Имя не может быть пустым")
        }
    }
}

let me = new Human("gfgffg")
console.log(me._name)
me.changeName("fgfgdgf")
console.log(me._name)

console.log(me._age)
me.changeAge(14)
console.log(me._age)

// Измените класс Human, добавив геттер и сеттер для возраста, который вычисляется на основании года рождения, соответственно, добавив в класс новое поле Год рождения.

class Human2 {
    _name = ""
    _sername = "silver"
    _age = 27
    _adress = "35 20"
    _birthday = 1997

    constructor(name) {
        this._name = name
    }

    changeName(newName) {
        if (newName != "") {
            this._name = newName
        }
        else {
            console.log("Ошибка, Имя не может быть пустым")
        }
    }

    set age(value) {
        this._age = value;
        this._birthday = 2024 - value
    }

    get age() {
        return this._age;
    }

}

let me2 = new Human2("ygabyga")
console.log(me2._name)
me2.changeName("sas")
console.log(me2._name)

console.log(me2.age)
me2.age = 14
console.log(me2._birthday)

// Класс Student наследуется от Human.Содержит поля Факультет, Курс, Группа, № зачетки.Метод для изменения значения поля Курс и Группа.Метод getFullName() – вывод имени и фамилии студента.
// Номер зачетки 71201300, где 7 – шифр факультета(7 - ФИТ, 6 - ИД), далее одна цифра шифр специальности(1 - ПОИТ, 2 - ИСИТ, 3 - ДЭВИ, 4 - ПОИБМС), 20 – две последние цифры года поступления, далее одна цифра – 1 - бюджет, 2 - платники, и три цифры - порядковый номер.

class Student extends Human2 {
    _facultet = "FIT"
    _kyrs = 2
    _group = 9
    _numberZachetki = 71232769


    changeKyrsGroup(kyrs, group) {
        if (kyrs > 0 && group > 0) {
            this._kyrs = kyrs
            this._group = group
        }
        else {
            console.log("Ошибка, курс или группа не может быть меньше нуля")
        }
    }

    getFullName() {
        console.log(`Имя: ${this._name}, Фамилия: ${this._sername}`)
    }

}

let student = new Student("queue")
student.getFullName()
console.log(student._kyrs)
console.log(student._group)
student.changeKyrsGroup(4, 1)
console.log(student._kyrs)
console.log(student._group)

// Класс Faculty.Содержит поля Название факультета, Количество групп, Количество студентов и соответствующие методы, изменяющие значения полей Количество групп и Количество студентов.Класс должен содержать метод getDev(), который выводит количество студентов специальности ДЭВИ(определяется из номера зачетки) и метод getGroupe() – выводит список студентов заданной группы.


class Faculty {
    constructor(facultyName, groupCount, studentCount) {
        this.facultyName = facultyName;
        this.groupCount = groupCount;
        this.studentCount = studentCount;
        this.studentRecords = []; // Список номеров зачеток студентов
    }

    // Метод для изменения количества групп
    setGroupCount(newGroupCount) {
        this.groupCount = newGroupCount;
    }

    // Метод для изменения количества студентов
    setStudentCount(newStudentCount) {
        this.studentCount = newStudentCount;
    }

    // Метод добавления номера зачетки студента
    addStudentRecord(record) {
        this.studentRecords.push(record);
    }

    // Метод, который возвращает количество студентов специальности ДЭВИ (шифр специальности 3)
    getDev() {
        const devStudents = this.studentRecords.filter(record => record.charAt(1) === '3');
        return devStudents.length;
    }

    // Метод, который возвращает список студентов заданной группы
    getGroupe(groupNumber) {
        // Предполагаем, что номер группы находится в номере зачетки, замените  на нужную логику
        const groupStudents = this.studentRecords.filter(record => record.slice(2, 4) === groupNumber);
        return groupStudents;
    }
}

// Пример использования
const fitFaculty = new Faculty("ФИТ", 10, 200);

// Добавляем студентов
fitFaculty.addStudentRecord("71201300");
fitFaculty.addStudentRecord("73201301");
fitFaculty.addStudentRecord("71203302");

// Получаем количество студентов ДЭВИ
console.log("Количество студентов специальности ДЭВИ:", fitFaculty.getDev());

// Получаем список студентов заданной группы
console.log("Список студентов группы 20:", fitFaculty.getGroupe("20"));