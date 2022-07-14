//Напишите функцию counter, которая при каждом вызове будет возвращать числа на 3 больше, чем в прошлый. Нельзя использовать переменные, объявленные через var!

let i = -3;

function counter() {
    i += 3;
    return i;
}

console.log(counter());  // Функция вернет 0
console.log(counter());  // Функция вернет 3
console.log(counter());  // Функция вернет 6
console.log(counter());  // Функция вернет 9
