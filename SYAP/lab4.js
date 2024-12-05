//1.Имеется список товаров. Реализуйте функции, которые добавляют, удаляют товар из списка, проверяет наличие товара. 
//Определите количество имеющего товара. Используйте коллекцию Set.  

let products = new Set();// Если товар уже существует, то он не добавится повторно, так как используется Set

function addProduct(product) {
    products.add(product);
}

function removeProduct(product) {
    products.delete(product);
}

function isProduct(product) {//проверяет, есть ли товар в списке.
    return products.has(product);
}

function countOfProduct()//возвращает количество товаров в списке.
{
    return products.size;
}

addProduct("Телевизор");
addProduct("Ноутбук");
addProduct("Телефон");
addProduct("Планшет");

console.log(isProduct("Ноутбук"));// true
console.log(isProduct("Наушники"));// false

console.log(countOfProduct());// 4


removeProduct("Планшет");

console.log(isProduct("Планшет"));// false
console.log(countOfProduct()); // 3

/*2.Используя коллекцию Set создайте список студентов. О каждом студенте содержится информация: номер зачетки, группа, ФИО. Создайте функции, которые:
- добавляют студента, 
- удаляют по номеру, 
- фильтруют список по группе, 
- сортируют по номеру зачетки. 
 */

let students = new Set();

function addStudent(student) {
    students.add(student);// Добавляем объект студента в Set
}

function removeStudent(studentId) {// Перебираем каждого студента в Set с помощью forEac
    students.forEach((student) => {
        if (student.studentId === studentId) {// Если ID студента совпадает с переданным ID
            students.delete(student);
        }
    });
}
// Функция для фильтрации студентов по группе
function filterStudent(group) {
    students.forEach((students) => {
        if (students.group == group) {
            console.log(students)
        }
    });
}
// Функция для сортировки студентов по studentId
function sortStudent() {
    return Array.from(students).sort((a, b) => a.studentId - b.studentId);
}


addStudent({ studentId: 9, group: "A", fio: "Борисов Никита" });
addStudent({ studentId: 7, group: "A", fio: "Орловская Полина" });
addStudent({ studentId: 6, group: "B", fio: "Карпенко Даша" });
addStudent({ studentId: 9, group: "C", fio: "Кондратчик Анна" });

filterStudent("A");
removeStudent(1);
filterStudent("C");

console.log(sortStudent());

/*3.Используя коллекцию Map и ее методы, реализуйте хранилище товаров. В корзине хранится информация о товаре: id (ключ в коллекции Map), название, количество товара, цена. Разработайте функции, которые:  
- добавляют товар, 
- удаляют товар из списка по id, 
- удаляют товары по названию (учтите, что названия товаров могут повторяться), 
- изменяют количество каждого товара,
- изменяют стоимость товара.
Рассчитайте количество позиций в списке и сумму стоимости всех товаров.
  */


let products1 = new Map();

function addProducts1(id, name, col, price) {
    products1.set(id, { name, col, price });//set-создать
}

function removeByID(id) {
    products1.delete(id);
}




function removeByName(name) {
    for (let [id, product1] of products1) // проходим все элементы до конца в каждом достовая значение id и объекта {name, col, price}
    {
        if (product1.name === name) {
            products1.delete(id);
        }
    }
}

function updateCol(id, newCol) //изменяем количество
{
    if (products1.has(id)) //имеет ли
    {
        const product1 = products1.get(id);//получает один продукт по id
        product1.col = newCol;
        products1.set(id, product1);
    }
}
function updatePrice(id, newPrice) {
    if (products1.has(id)) {
        const product1 = products1.get(id);
        product1.price = newPrice;
        products1.set(id, product1);
    }
}


function getProductCount() {
    return products1.size;
}

function getTotalPrice() {
    let totalPrice = 0;
    for (const product1 of products1.values()) {
        totalPrice += product1.col * product1.price;
    }
    return totalPrice;
}

// Пример использования функций
addProducts1(1, "Телефон", 2, 100);
addProducts1(2, "Ноутбук", 1, 500);
addProducts1(3, "Телевизор", 3, 200);

console.log(getProductCount()); // 3  количество всех продуктов 
console.log(getTotalPrice()); // 1300

removeByID(2);
console.log(getProductCount()); // 2
console.log(getTotalPrice()); // 800

removeByName("Телефон");
console.log(getProductCount()); // 1
console.log(getTotalPrice()); // 600

updateCol(3, 5);//id и количество(телефизорЫ)
console.log(getTotalPrice()); // 1000

updatePrice(3, 250);
console.log(getTotalPrice()); // 1250

/*4.Создайте коллекцию WeakMap для кеширования результатов функции. WeakMap должен содержать входные параметры функции и результаты расчета.  Функция должна выполняться только в том случае, если в кэше нет данных, иначе – берем данные из WeakMap. */


const cache = new WeakMap();

// Функция для кэширования результатов
function cachedFunction(func) {
    return function (...args) {
        // Проверяем, есть ли результат для данного набора аргументов в кэше
        if (cache.has(func) && cache.get(func)[args]) {
            console.log('Данные взяты из кэша');
            return cache.get(func)[args];
        }

        // Выполняем функцию, так как результатов в кэше нет
        const result = func(...args);

        // Создаем новый кэш для функции, если его еще нет
        if (!cache.has(func)) {
            cache.set(func, {});
        }

        // Сохраняем результат в кэше
        cache.get(func)[args] = result;

        console.log('Результаты вычислений сохранены в кэше');
        return result;
    };
}


function calculateExpensiveValue(base, exponent) {
    console.log('Выполняется вычисление...');
    return Math.pow(base, exponent);
}

const cachedCalculate = cachedFunction(calculateExpensiveValue);

// Пример использования
console.log(cachedCalculate(2, 3)); // Выполняется вычисление... 8
console.log(cachedCalculate(2, 3)); // Выполняется вычисление... 8
console.log(cachedCalculate(3, 3)); // Данные взяты из кэша 27
console.log(cachedCalculate(4, 2)); // Выполняется вычисление... 16
console.log(cachedCalculate(4, 2)); // Данные взяты из кэша 16

console.log(cachedCalculate(3, 3)); 