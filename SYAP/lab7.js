//1.Создайте объект person с методами greet (сообщение с приветствием пользователя) и ageAfterYears (принимает years и возвращает “текущий возраст” + years), которые используют this для доступа к свойствам объекта.

let person = {

    name: "Jhone",

    age: 20,

    ageAfterYears(age) {
        return this.age + age
    },

    greet() {
        console.log("Привет!")
    }
}

person.greet()

console.log(person.ageAfterYears(10))

//2. Создайте объект car, который имеет свойства model и year, а также метод getInfo, который выводит информацию о машине.

let car = {
    model: "Honda Civic",
    year: 2021,
    getInfo() {
        console.log(`Модель машины: ${this.model}, год выпуска: ${this.year}`)
    }
}

car.getInfo()

//3. Создайте функцию-конструктор Book, которая создает объекты с методами getTitle и getAuthor.

function Book(title) {
    this.title = title;
    this.author = "someOne";
    this.getTitle = function () {
        console.log(this.title)
    }
    this.getAuthor = function () {
        console.log(this.author)
    }
}
let newBook = new Book("Piece and War")

newBook.getTitle()
newBook.getAuthor()



//4. Создайте объект team, который содержит массив игроков и метод для вывода информации о каждом игроке. Используйте this в вложенной функции.

let team = {
    players: ["firstPlayer", "secondPlayer", "thirdPlayer"],
    showInfo() {
        for (pers of this.players) {
            console.log(pers)
        }
    }
}

team.showInfo()


//5. Создайте модуль counter, который инкапсулирует переменную count и предоставляет методы для инкрементации, декрементации и получения текущего значения. Используйте this для доступа к свойствам.

const counter = (function () {
    let count = 0;


    return {
        increment() {
            count++;
            return count;
        },
        decrement() {
            count--;
            return count;
        },
        getCount() {
            return count;
        }
    };
})();

console.log(counter.increment());
console.log(counter.increment());
console.log(counter.decrement());
console.log(counter.getCount());

//6. Создайте объект item со свойством price. Сначала определите его с параметрами, разрешающими изменение и удаление. Затем переопределите дескрипторы так, чтобы свойство стало неизменяемым.

let item = {
    price: 15,
    name: "someItem"
}

console.log(item.price)

Object.defineProperty(item, "price", {
    value: 20,
    writable: false,
});

let descriptor = Object.getOwnPropertyDescriptor(item, 'price');

console.log(JSON.stringify(descriptor, null, 2));

console.log(item)
item.price = 2
console.log(item)


//7. Создайте объект circle, который имеет свойство radius. Добавьте геттер для вычисления площади круга на основе радиуса, геттер и сеттер для изменения радиуса.

const createCircle = (initialRadius = 1) => {
    let _radius = initialRadius;

    return {
        get radius() {
            return _radius;
        },

        set radius(newRadius) {
            if (newRadius > 0) {
                _radius = newRadius;
            } else {
                console.log("Радиус должен быть положительным числом.");
            }
        },

        get area() {
            return Math.PI * _radius ** 2;
        }
    };
};

const circle = createCircle();

console.log(circle.radius);
console.log(circle.area);

circle.radius = 5;
console.log(circle.radius);
console.log(circle.area);

circle.radius = -3;


//8. Создайте объект car с тремя свойствами: make, model, и year. Сначала определите их с параметрами, разрешающими изменение и удаление. Затем переопределите дескрипторы, чтобы все свойства стали неизменяемыми.

let car2 = {
    make: "делает",
    model: "BMW m5",
    year: 2015,
}

Object.defineProperty(car2, "make", {
    configurable: false
});
Object.defineProperty(car2, "model", {
    configurable: false
});
Object.defineProperty(car2, "year", {
    configurable: false
});


//9. Создайте массив, в котором будет три числа. Используя Object.defineProperty, добавьте свойство sum (геттер), которое будет возвращать сумму всех элементов массива. Сделайте это свойство доступным только для чтения.


let massive = [2, 3, 4]

Object.defineProperty(massive, "sum", {
    get() {
        return this.reduce((acc, num) => acc + num, 0);
    },
    enumerable: true,   // делает свойство перечисляемым
    configurable: false // делает свойство неизменяемым
});

console.log(massive.sum)
if (delete massive.sum) {
    console.log('Свойство удалено');
} else {
    console.log('Свойство не удалось удалить');
}



//10. Создайте объект rectangle, который имеет свойства width и height. Добавьте геттер для вычисления площади прямоугольника, геттеры и сеттеры для ширины и высоты.

const rectangle = (width = 10, height = 10) => {
    let _width = width;
    let _height = height;

    return {

        get width() {
            return _width;
        },

        set width(newWidth) {
            if (newWidth > 0) {
                _width = newWidth;
            } else {
                console.log("Ширина должна быть положительным числом.");
            }
        },

        get height() {
            return _height;
        },

        set height(newHeight) {
            if (newHeight > 0) {
                _height = newHeight;
            } else {
                console.log("Высота должна быть положительным числом.");
            }
        },

        get area() {
            return _width * _height;
        }
    };
};

const rectangle1 = rectangle();

console.log(rectangle1.area);
rectangle1.height = 20;

console.log(rectangle1.area);

//11. Создайте объект user, который имеет свойства firstName и lastName. Добавьте геттер для получения полного имени и сеттер для изменения полного имени.

const user = {
    firstName: "jt",
    lastName: "bbr",
    get fullName() {
        return `Полное имя: ${this.lastName} ${this.firstName}`;
    },
    set fullName(value) {
        [this.lastName, this.firstName] = value.split(" ");
    }
}

console.log(user.fullName); // Полное имя

user.fullName = "Mc Jax";

console.log(user.firstName); // Mc
console.log(user.lastName);  // Jax
console.log(user.fullName);  // Полное имя: Mc Jax