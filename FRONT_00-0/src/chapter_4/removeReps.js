// Вам нужно написать функцию которая принимает в кач-ве аргумента массива чисел и удаляет все повторяющиеся значения

function removeReps(array) {
    let new_array = [];
    for (let i = 0; i < array.length; i++) {
        let j;
        for (j = 0; j < new_array.length; j++) {
            if (array[i] === new_array[j]) {
                break
            }
        }

        if (j >= new_array.length || array[i] !== new_array[j]) {
            new_array.push(array[i]);
        }
    }

    return new_array;
}

console.log(removeReps([1, 1, 2, 4, 5, 6, 6, 8, 9, 11])); // [1,2,4,5,6,8,9,11]
console.log(removeReps([1,1,1,1])); // [1]
console.log(removeReps([1,2,3,4,5,6])); // [1,2,3,4,5,6]

