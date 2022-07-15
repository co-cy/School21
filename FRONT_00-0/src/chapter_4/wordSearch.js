//  В этой задаче нужно будет написать алгоритм поиска, который скажет, можно ли найти входное слово в головоломке поиска слов, которая тоже подается функции на вход.
// Данная задача имеет два уровня сложности :
// - Первый уровень включает в себя исключительно поиск по вертикали и по горизонтали
// - Второй уровень дополнительно включает в себя поиск по диагонали
// - Слова могут быть записаны слева направо и наоборот.

function pos_is_good(puzzle, row, col) {
    return row >= 0 && col >= 0 && puzzle.length && row < puzzle.length && col < puzzle[0].length;
}


function findWordAtPoint(puzzle, word, row, col) {
    // Horizontal
    let cur_symbol = 0;
    for (let t_col = col; t_col < puzzle[0].length; t_col++) {
        if (pos_is_good(puzzle, row, t_col) && puzzle[row][t_col] === word[cur_symbol]) {
            cur_symbol++;
            if (cur_symbol === word.length) {
                return true;
            }
        } else {
            break;
        }
    }

    // Diagonal
    cur_symbol = 0;
    for (let t_row = row, t_col = col; t_row < puzzle.length && t_col < puzzle[0].length; t_row++, t_col++) {
        if (pos_is_good(puzzle, t_row, t_col) && puzzle[t_row][t_col] === word[cur_symbol]) {
            cur_symbol++;
            if (cur_symbol === word.length) {
                return true;
            }
        } else {
            break;
        }
    }

    // Diagonal2
    cur_symbol = 0;
    for (let t_row = row, t_col = col; t_row < puzzle.length && t_col < puzzle[0].length; t_row++, t_col--) {
        if (pos_is_good(puzzle, t_row, t_col) && puzzle[t_row][t_col] === word[cur_symbol]) {
            cur_symbol++;
            if (cur_symbol === word.length) {
                return true;
            }
        } else {
            break;
        }
    }


    // Vertical
    cur_symbol = 0;
    for (let t_row = row; t_row < puzzle.length; t_row++) {
        if (pos_is_good(puzzle, t_row, col) && puzzle[t_row][col] === word[cur_symbol]) {
            cur_symbol++;
            if (cur_symbol === word.length) {
                return true;
            }
        } else {
            break;
        }
    }

}


function searchSubString(puzzle, word) {
    let copy_word = word;
    for (let i = 0; i < 2; i++) {
        for (let row = 0; row < puzzle.length; row++) {
            for (let col = 0; col < puzzle[0].length; col++) {
                if (puzzle[row][col] === copy_word[0] && findWordAtPoint(puzzle, copy_word, row, col)) {
                    return true;
                }
            }
        }
        copy_word = copy_word.split('').reverse().join('');
    }

    return false;
}

const examplePuzzle = [
    ["b", "l", "g", "o", "l", "d", "s"],
    ["x", "k", "q", "w", "i", "j", "p"],
    ["a", "n", "w", "k", "k", "p", "n"],
    ["h", "e", "e", "e", "k", "i", "l"],
    ["q", "e", "k", "a", "y", "q", "a"],
    ["h", "u", "h", "a", "e", "a", "u"],
    ["k", "q", "j", "c", "c", "m", "r"],
];

console.log(searchSubString(examplePuzzle, "gka"));

// Level 1
console.log(searchSubString(examplePuzzle, "like")); // true
console.log(searchSubString(examplePuzzle, "gold")); // true
console.log(searchSubString(examplePuzzle, "queen")); // true

// Level 2
console.log(searchSubString(examplePuzzle, "cake")); // true

