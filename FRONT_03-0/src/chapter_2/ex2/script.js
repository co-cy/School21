let number_0 = document.getElementById("number_0");
let number_1 = document.getElementById("number_1");
let number_2 = document.getElementById("number_2");
let number_3 = document.getElementById("number_3");
let number_4 = document.getElementById("number_4");
let number_5 = document.getElementById("number_5");
let number_6 = document.getElementById("number_6");
let number_7 = document.getElementById("number_7");
let number_8 = document.getElementById("number_8");
let number_9 = document.getElementById("number_9");

let sum = document.getElementById("sum");
let sub = document.getElementById("sub");
let mul = document.getElementById("mul");
let div = document.getElementById("div");

let point = document.getElementById("point");
let clear = document.getElementById("clear");
let eq = document.getElementById("eq");

let expression = document.getElementById("text");

number_0.addEventListener("click" , () => addText(0));
number_1.addEventListener("click" , () => addText(1));
number_2.addEventListener("click" , () => addText(2));
number_3.addEventListener("click" , () => addText(3));
number_4.addEventListener("click" , () => addText(4));
number_5.addEventListener("click" , () => addText(5));
number_6.addEventListener("click" , () => addText(6));
number_7.addEventListener("click" , () => addText(7));
number_8.addEventListener("click" , () => addText(8));
number_9.addEventListener("click" , () => addText(9));
point.addEventListener("click" , () => addText('.'));

sum.addEventListener("click" , () => addText(' +'));
sub.addEventListener("click" , () => addText(' -'));
mul.addEventListener("click" , () => addText(' *'));
div.addEventListener("click" , () => addText(' /'));

clear.addEventListener("click" , clearExpression);

eq.addEventListener("click" , eqExpression);


let is_eq = false;

function setText(text) {
    expression.value = text;
}

function getText() {
    if (is_eq) {
        is_eq = false;
        clearExpression();
    }
    console.log(expression.value);
    return expression.value;
}

function addText(text) {
    setText(getText() + text);
}

function clearExpression() {
    setText("");
    console.log("AFTE", expression.value);
}

function eqExpression() {
    try {
        setText(eval(getText()));
    } catch (err) {
        setText("ОШИБКА");
    } finally {
        is_eq = true;
    }
}
