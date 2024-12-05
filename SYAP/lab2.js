//ЗАДАНИЕ 1
function basicOperation(operation, value1, value2) {
    let result

    switch (operation) {
        case '+':  
            result = value1 + value2
            break

        case '-': 
            result = value1 - value2
            break

        case '*':
            result = value1 * value2
            break

        case '/':
            result = value1 / value2
            break
        default:
            console.log('Некорректный ввод знака операции')
            break
    }

    return result
}

console.log(basicOperation('*', 5, 10))

//ЗАДАНИЕ 2. Реализовать функцию, которая принимает число n и возвращает сумму кубов всех чисел до n включительно. 

function kubeForN(n) {
    let result = 0

    for (let i = 1; i <= n; i++) {
        result += i ** 3
    }
    return result
}
console.log(kubeForN(3))

//ЗАДАНИЕ 3. Реализовать функцию, которая принимает один аргумент – массив чисел и возвращает среднее арифметическое всех элементов массив

function sumArrayElem(arr) {
    let result = 0

    arr.forEach(element => {
        result += element
    });

    return result / arr.length;
}
console.log(sumArrayElem([5, 10, 3]))


//ЗАДАНИЕ 4. Реализовать функцию, которая получает строку str, переворачивает ее и возвращает строку, состоящую только из символов английского алфавита.


function reverseStr(str) {
    let reverse = str.replace(/[а-яё]|[0-9]|[?]|[' ']/gi, '').split('').reverse().join('');
    return reverse
}
console.log(reverseStr("JavaScr53эфч? ipt"))

//ЗАДАНИЕ 5. Напишите функцию, которая принимает целое число n и строку s в качестве параметров и возвращает строку s, повторяющуюся ровно n раз.

function repeatStr(str, n) {
    let result = ''

    for (let i = 0; i < n; i++) {
        result += str
    }

    return result
}
console.log(repeatStr("ipt", 3))

//ЗАДАНИЕ 6. Напишите функцию, которая принимает два массива строк arr1 и arr2. Функция возвращает массив arr3, которые содержит строки из arr1, но не входящие в arr2.

function filterStrings(arr1, arr2) {
    let arr3 = arr1.filter((str) => {
        return !arr2.includes(str)
    })
    return arr3;
}
console.log(filterStrings(['apple', 'banana', 'orange', 'kiwi'], ['banana', 'kiwi', 'grape']))
// function flattenArray(arr, depth = Infinity) {
//     return arr.reduce((acc, val) => {
        
//         if (Array.isArray(val) && depth > 0) {
//             return acc.concat(flattenArray(val, depth - 1)); 
//         } else {
//             return acc.concat(val); 
//         }
//     }, []);
// }

// console.log(flattenArray([1, [1, 2, [3, 4, [5, 6]]], [2, 4], [[7, 8], 9]], 2)); 

