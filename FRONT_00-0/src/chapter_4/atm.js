// Напишите функцию банкомат которая принимает на вход число и возвращает объект в формате  {номинал_купюры : количество_купюр}.
// Если банкомат не может выдать данную сумму, то выводится ошибка 'Incorrect value'.
// Купюры должны выдаться оптимальным образом (вместо 5 купюр номиналом 1000 выдается одна 5000).
// За раз банкомат может выдавать не более 20 купюр, если купюр для выдачи не хватает то выводится ошибка 'Limit exceeded'

function atm(sum) {
    const banknots = [5000, 2000, 1000, 500, 200, 100, 50];
    let result = {};

    let count_banknots = 0;

    for (let banknot of banknots) {
        result[banknot] = 0;
        while (banknot <= sum) {
            result[banknot] += 1;
            sum -= banknot;
            if (++count_banknots > 20) {
                return "Limit exceeded"
            }
        }
    }

    if (sum) {
        return 'Incorrect value';
    } else {
        return result;
    }
}


console.log(atm(8350)); // {5000 : 1, 2000 : 1, 1000 : 1, 200 : 1, 100 : 1, 50 : 1 }
console.log(atm(8300)); // {5000 : 1, 2000 : 1, 1000 : 1, 200 : 1, 100 : 1, 50 : 1 }
console.log(atm(20000)); // {5000 : 1, 2000 : 1, 1000 : 1, 200 : 1, 100 : 1, 50 : 1 }
console.log(atm(2570)); // Incorrect value
console.log(atm(100050)); // limit exceeded


