/*1.Имеется массив numbers. Сохранить первый элемент массива в переменную y используя деструктуризацию.*/

let numbers = [1, 2, 3, 4]

let first

[first, sec] = numbers

console.log(first, sec)

/*2.Объект user имеет свойства name, age. Создайте объект admin, у которого есть свойства admin и все свойства объекта user. Используйте spread оператор.*/

let user = {
    name: "kekw",
    age: 52
}

let admin = {
    ...user,
    delUs: "delet"
}
console.log(admin)

// /*3.Выполнить деструктуризацию объекта store до 3 уровня вложенности. После этого вывести значения likesCount из массива posts. Выполнить фильтрацию массива dialogs – выбрать пользователей с четными id.   В массиве messages заменить все сообщения на “Hello user” (использовать метод map).*/

let store = {
    state: {  // 1 уровень
        profilePage: {  // 2 уровень
            posts: [  // 3 уровень
                { id: 1, message: 'Hi', likesCount: 12 },
                { id: 2, message: 'By', likesCount: 1 },
            ],
            newPostText: 'About me',
        },
        dialogsPage: {
            dialogs: [
                { id: 1, name: 'Valera' },
                { id: 2, name: 'Andrey' },
                { id: 3, name: 'Sasha' },
                { id: 4, name: 'Viktor' },
            ],
            messages: [
                { id: 1, message: 'hi' },
                { id: 2, message: 'hi hi' },
                { id: 3, message: 'hi hi hi' },
            ],
        },
        sidebar: [],
    },
}

const {
    state: {
        profilePage: {
            posts
        },
        dialogsPage: {
            dialogs, messages
        }
    }
} = store;

// 1. Вывод likesCount из массива posts
posts.forEach(post => {
    console.log(post.likesCount); // выводим значения likesCount
});

// // 2. Фильтрация массива dialogs — выбор пользователей с четными id
const evenDialogs = dialogs.filter(dialog => dialog.id % 2 === 0);
console.log(evenDialogs); // выводим отфильтрованные диалоги


// // 3. Заменяем все сообщения в массиве messages на "Hello user"
const updatedMessages = messages.map(message => ({ ...message, message: 'Hello user' }));
console.log(updatedMessages); // выводим обновленные сообщения


/*4.В массиве tasks хранится список задач. Создать новую задачу task и добавить ее в массив, используя spread оператор.*/

let tasks = [
    { id: 1, title: "HTML&CSS", isDone: true },
    { id: 2, title: "JS", isDone: true },
    { id: 3, title: "ReactJS", isDone: false },
    { id: 4, title: "Rest API", isDone: false },
    { id: 5, title: "GraphQL", isDone: false },
];

tasks = [...tasks, { id: 6, title: "angular", isDone: false }]

console.log(tasks)

// /*5.Массив [1, 2, 3] передайте в качестве параметра функции sumValues. Используйте spread оператор.*/


function sumValues(x, y, z) {
    return x + y + z;
}

console.log(sumValues(...[1, 2, 3]))