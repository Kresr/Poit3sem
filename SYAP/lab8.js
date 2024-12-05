/*1.Выполнить глубокое копирование всех объектов и массивов. Использовать spread оператор */

/*Глубокое копирование — это процесс создания точной копии объекта, в котором все вложенные объекты и массивы также копируются рекурсивно. В результате изменения в скопированном объекте не затрагивают исходный объект, и наоборот. */

/*При глубоком копировании копируется каждый уровень объекта или массива, что предотвращает изменения во вложенных структурах исходного объекта. */
//1)
let user = {
    name: 'Masha',
    age: 21
};
let copyUser = { ...user };


//2)
let numbers = [1, 2, 3];
let copyNumbers = [...numbers];


//3)
let user1 = {
    name: 'Masha',
    age: 23,
    location: {
        city: 'Minsk',
        country: 'Belarus'
    }
};
let copyUser1 = {
    ...user1,
    location: { ...user1.location }// Создаем глубокую копию только для свойства location
};
console.log("Мой пример номер(3))")
copyUser1.location.city = 'Pinsk';// Изменяем город в копии
console.log(copyUser1);
console.log(user1);


//4)
let user2 = {
    name: 'Masha',
    age: 28,
    skkills: ["HTML", "CSS", "JavaScript", "React"]
};
let copyUser2 = {
    ...user2,// Поверхностная копия объекта user2
    skkills: [...user2.skkills]
};
console.log("Мой пример (4)");
copyUser2.skkills.push("OOP");
console.log(copyUser2);


//5)
const array = [
    { id: 1, name: 'Vasya', group: 10 },
    { id: 2, name: 'Ivan', group: 11 },
    { id: 3, name: 'Masha', group: 12 },
    { id: 4, name: 'Petya', group: 10 },
    { id: 5, name: 'Kira', group: 11 },
]
console.log("Еще один примерчик (5)")
let copyArray = array.map(el => ({ ...el }));
console.log(copyArray);
/*Метод map() является встроенным методом массива в JavaScript. Он создаёт новый массив, заполняя его результатами вызова предоставленной функции для каждого элемента массива.

Это стрелочная функция, которая принимает один аргумент el. Она используется для преобразования каждого объекта в массиве. */
/*Оператор распространения (spread operator) используется для создания нового объекта, который содержит все свойства текущего объекта el.
Этот оператор берёт все свойства объекта el и "разворачивает" их в новый объект.
Например, если el равен {id: 1, name: 'Vasya', group: 10}, то {...el} создаёт новый объект {id: 1, name: 'Vasya', group: 10}. */

//6)
let user4 = {
    name: 'Masha',
    age: 19,
    studies: {
        university: 'BSTU',
        speciality: 'designer',
        year: 2020,
        exams: {
            maths: true,
            programming: false
        }
    }
};
let copyUser4 = {
    ...user4,
    studies: {
        ...user4.studies,
        exams: { ...user4.exams }
    }
};
console.log("Мой пример(6)")
copyUser4.studies.speciality = "PI";
console.log(copyUser4);


//7)
// let user5 = {
//     name: 'Masha',
//     age: 22,
//     studies: {
//         university: 'BSTU',
//         speciality: 'designer',
//         year: 2020,
//         department: {
//             faculty: 'FIT',
//             group: 10,
//         },
//         exams: [
//             { maths: true, mark: 8 },
//             { programming: true, mark: 4 }
//         ]
//     }
// };

// // Глубокое копирование объекта user5 с использованием spread оператора
// let user5Copy = {
//     ...user5, // поверхностное копирование верхнего уровня
//     studies: {
//         ...user5.studies, // копирование вложенного объекта studies
//         department: {
//             ...user5.studies.department // копирование объекта department
//         },
//         exams: user5.studies.exams.map(exam => ({ ...exam })) // копирование массива exams и его элементов
//     }
// };

// console.log(user5Copy);


//8)
// let user6 = {
//     name: 'Masha',
//     age: 21,
//     studies: {
//         university: 'BSTU',
//         speciality: 'designer',
//         year: 2020,
//         department: {
//             faculty: 'FIT',
//             group: 10,
//         },
//         exams: [
//             { 
//                 maths: true,
//                 mark: 8,
//                 professor: {
//                     name: 'Ivan Ivanov',
//                     degree: 'PhD'
//                 }
//             },
//             { 
//                 programming: true,
//                 mark: 10,
//                 professor: {
//                     name: 'Petr Petrov',
//                     degree: 'PhD'
//                 }
//             },
//         ]
//     }
// };
// // Глубокое копирование объекта user6 с использованием spread оператора
// let user6Copy = {
//     ...user6, // поверхностное копирование верхнего уровня
//     studies: {
//         ...user6.studies, // копирование вложенного объекта studies
//         department: {
//             ...user6.studies.department // копирование объекта department
//         },
//         exams: user6.studies.exams.map(exam => ({
//             ...exam, // копирование каждого объекта в массиве exams
//             professor: {
//                 ...exam.professor // копирование объекта professor внутри каждого экзамена
//             }
//         }))
//     }
// };

// console.log(user6Copy);



/*2.Обратитесь к копии объекта user5 и измените значение свойства group на 12, 
а оценку по программированию измените на 10.*/

let user5 = {
    name: 'Masha',
    age: 22,
    studies: {
        university: 'BSTU',
        speciality: 'designer',
        year: 2020,
        department: {
            faculty: 'FIT',
            group: 10,
        },
        exams: [
            { maths: true, mark: 8 },
            { programming: true, mark: 4 }
        ]
    }
};

// Глубокое копирование объекта user5
let copyUser5 = {
    ...user5,
    studies: {
        ...user5.studies,
        department: {
            ...user5.studies.department
        },
        exams: user5.studies.exams.map(exam => ({
            ...exam
        }))
    }
};
// Изменение значения свойства group на 12
copyUser5.studies.department.group = 12;
// Изменение оценки по программированию на 10
copyUser5.studies.exams[1].mark = 10;

console.log("ВТОРОЕ ЗАДАНИЕ");
console.log(copyUser5);
console.log(user5);



/*3.Обратитесь к копии объекта user6 и измените имя преподавателя.*/
let user6 = {
    name: 'Masha',
    age: 21,
    studies: {
        university: 'BSTU',
        speciality: 'designer',
        year: 2020,
        department: {
            faculty: 'FIT',
            group: 10,
        },
        exams: [
            {
                maths: true,
                mark: 8,
                professor: {
                    name: 'Ivan Ivanov',
                    degree: 'PhD'
                }
            },
            {
                programming: true,
                mark: 10,
                professor: {
                    name: 'Petr Petrov',
                    degree: 'PhD'
                }
            },
        ]
    }
};
let copyUser6 = {
    ...user6,
    studies: {
        ...user6.studies,
        exams: user6.studies.exams.map(exam => ({
            ...exam,
            professor: { ...exam.professor },
        }))
    }
};
console.log("ТРЕТЬЕ ЗАДАНИЕ")
copyUser6.studies.exams[0].professor.name = "Beloded Nikolay";
console.log(copyUser6);
console.log(user6);




/*4.Обратитесь к копии объекта user7 и измените количество страниц 
на 3 для статьи “About CSS” преподавателя Petr Ivanov.*/

let user7 = {
    name: 'Masha',
    age: 20,
    studies: {
        university: 'BSTU',
        speciality: 'designer',
        year: 2020,
        department: {
            faculty: 'FIT',
            group: 10,
        },
        exams: [
            {
                maths: true,
                mark: 8,
                professor: {
                    name: 'Ivan Petrov',
                    degree: 'PhD',
                    articles: [
                        { title: "About HTML", pagesNumber: 3 },
                        { title: "About CSS", pagesNumber: 5 },
                        { title: "About JavaScript", pagesNumber: 1 },
                    ]
                }
            },
            {
                programming: true,
                mark: 10,
                professor: {
                    name: 'Petr Ivanov',
                    degree: 'PhD',
                    articles: [
                        { title: "About HTML", pagesNumber: 3 },
                        { title: "About CSS", pagesNumber: 5 },
                        { title: "About JavaScript", pagesNumber: 1 },
                    ]
                }
            },
        ]
    }
};

// Глубокое копирование объекта user7
let copyUser7 = {
    ...user7,
    studies: {
        ...user7.studies,
        department: {
            ...user7.studies.department // Копируем department
        },
        exams: user7.studies.exams.map(exam => ({
            ...exam,
            professor: {
                ...exam.professor,
                articles: exam.professor.articles.map(article => ({ ...article })) // Копируем articles
            }
        }))
    }
};

console.log("ЧЕТВЕРТОЕ ЗАДАНИЕ");

// Изменение количества страниц для статьи "About CSS" преподавателя Petr Ivanov
copyUser7.studies.exams[1].professor.articles[1].pagesNumber = 3;

console.log(copyUser7);



/*5.Замените все сообщения в объекте store на “Hello”.*/

let store = {
    state: {
        profilePage: {
            posts: [
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
};
console.log(store)

// Глубокое копирование объекта store
let copyStore = {
    state: {
        ...store.state,
        profilePage: {
            ...store.state.profilePage,
            posts: store.state.profilePage.posts.map(post => ({ ...post })),
        },
        dialogsPage: {
            ...store.state.dialogsPage,
            dialogs: store.state.dialogsPage.dialogs.map(dialog => ({ ...dialog })),
            messages: store.state.dialogsPage.messages.map(message => ({ ...message })),
        },
        sidebar: [...store.state.sidebar],
    },
};

console.log("ПЯТОЕ ЗАДАНИЕ");

// Замена всех сообщений на "Hello"
copyStore.state.dialogsPage.messages = copyStore.state.dialogsPage.messages.map(m => ({
    id: m.id,
    message: "Hello"
}));


console.log(copyStore);