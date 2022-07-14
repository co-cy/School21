// Вам надо набор функций который будет симулировать калькулятор.
// Для этого вам надо написать 9 функций, которые могут! принимать в кач - ве аргумента другую функцию, если функция передана, то надо вернуть вызов функции с числом n, иначе вернуть число n.
// Например, функция one может принять в кач - ве аргумента функцию sum, тогда в return будет sum(1).Если же в функцию не передали ничего, то она просто вернет 1.
// Также надо написать 4 функции основных арифмитических операторов, которые принимают в кач-ве аргумента первое число, а возвращают функцию, которая принмает в кач-ве аргумента второе число и возвращает их сумму/разность/частое/произведение

function number_callback(number, callback) {
    if (callback)
        return callback(number)
    return number;
}

function one(callback) {
    return number_callback(1, callback);
}

function two(callback) {
    return number_callback(2, callback);
}

function three(callback) {
    return number_callback(3, callback);
}

function four(callback) {
    return number_callback(4, callback);
}

function five(callback) {
    return number_callback(5, callback);
}

function six(callback) {
    return number_callback(6, callback);
}

function seven(callback) {
    return number_callback(7, callback);
}

function eight(callback) {
    return number_callback(8, callback);
}

function nine(callback) {
    return number_callback(9, callback);
}

function plus(a) {
    return function (n) { return a + n };
}

function minus(a) {
    return function (n) { return a - n };
}

function divide(a) {
    return function (n) { return a / n };
}

function mult(a) {
    return function (n) { return a * n };
}

console.log(one(plus(one())))
console.log(one(mult(three(plus(four()))))); // В итоге вернется 7
