// Вам нужно написать функция для решения Судоку. Функция принимает один аргумент - строку, в ней на месте пропущенных цифр стоят -.
// Функция должна вернуть строку, в которой все значения будут заполнены.

// Давайте сыграем в настоящую головоломку Судоку, обращая внимание на то, как мы приближаемся к решению поставленной задачи.
// - Какие стратегии мы принимаем и почему?
// - Как мы выбираем, с чего начать?
// - Как мы узнаем, когда действительно следует поставить число в клетку?
// - Что мы делаем, когда мы окончательно не знаем, как заполнить остальные клетки?
// Размышляя о нашей человеческой стратегии, важно понимать, что иногда стратегии, которые работают для людей, будет трудно реализовать на компьютере.
// Однако верно и обратное: стратегии компьютера могут быть не всегда удобны для людей, потому что нам придется писать слишком много текста, использовать слишком много листов бумаги или помнить много информации, которую в состоянии запомнить компьютер, но не человек.
// Обязательно напишите метод `printPrettyBoard`, который берет доску, записанную в строчку и возвращает отформатированный вариант, более привычный для нашего визуального восприятия. Например:


// Ниже представленны тестовые данные для вашей функции, они имеют 3 уровня сложности
// * Пять головоломок могут быть решены с помощью базовой логики.
// * Пять требуют немного более продвинутой логики.
// * Пять требуют от вашего решателя умения угадывать и перерешивать, если зашёл в тупик.

function r_solve(puzzle) {
    let min_pos_value_count_cell = null;
    while (true) {
        min_pos_value_count_cell = null;
        for (let row = 0; row < 9; row++) {
            for (let col = 0; col < 9; col++) {
                if (puzzle[row][col] !== '-') {
                    continue;
                }

                let pos_val = findPossibleValues(puzzle, row, col);
                if (pos_val.size === 0)
                    return null;
                if (pos_val.size === 1) {
                    puzzle[row][col] = pos_val.values().next().value;
                }
                if (!min_pos_value_count_cell || (pos_val.size < min_pos_value_count_cell[1].size)) {
                    min_pos_value_count_cell = [[row, col], pos_val];
                }
            }
        }
        if (!min_pos_value_count_cell)
            return puzzle;
        else if (1 < min_pos_value_count_cell[1].size)
            break;
    }

    let row = min_pos_value_count_cell[0][0];
    let col = min_pos_value_count_cell[0][1];

    for (let pos_value of min_pos_value_count_cell[1]) {
        let copy_puzzle = copy(puzzle);

        copy_puzzle[row][col] = pos_value;

        let res = r_solve(copy_puzzle);
        if (res)
            return res;
    }

}

function copy(puzzle) {
    let copy_puzzle = [];

    for (let row = 0; row < puzzle.length; row++) {
        copy_puzzle.push([]);
        for (let col = 0; col < puzzle[0].length; col++) {
            copy_puzzle[row].push(puzzle[row][col]);
        }
    }

    return copy_puzzle;
}

function getRowValues(puzzle, row) {
    return new Set(puzzle[row]);
}

function getColumnValues(puzzle, column) {
    let values = new Set();

    for (let row = 0; row < puzzle.length; row++) {
        values.add(puzzle[row][column]);
    }

    return values;
}

function getBlockValues(puzzle, row, column) {
    let values = new Set();

    let blockStartRow = 3 * ((row - row % 3) / 3);
    let blockStartColumn = 3 * ((column - column % 3) / 3);

    for (let row = 0; row < 3; row++)
        for (let col = 0; col < 3; col++)
            values.add(puzzle[blockStartRow + row][blockStartColumn + col]);

    return values;
}

function findPossibleValues(puzzle, row, column) {
    let was_values = new Set([
        ...getBlockValues(puzzle, row, column),
        ...getRowValues(puzzle, row),
        ...getColumnValues(puzzle, column)])

    let possible_value = new Set();

    for (let i = 1; i < 10; i++)
        if (!was_values.has(i))
            possible_value.add(i);

    return possible_value;
}

function gayStyle(puzzle) {
    let beautiful_puzzle = [];

    for (let row = 0; row < 9; row++) {
        beautiful_puzzle.push([]);
        for (let col = 0; col < 9; col++) {
            let val = puzzle[row * 9 + col];
            if (val === '-') {
                beautiful_puzzle[row].push('-');
            } else {
                beautiful_puzzle[row].push(val - '0');
            }
        }
    }

    return beautiful_puzzle;
}

function solve(puzzle) {
    puzzle = gayStyle(puzzle);
    return r_solve(puzzle);
}

function printPrettyBoard(puzzle) {
    let string = []
    for (let row = 0; row < puzzle.length; row++) {
        if (!row)
            string.push(" |");
        else
            string.push("|");

        for (let col = 0; col < puzzle[0].length; col++)
            string = string.concat(['\t', puzzle[row][col], '|']);
        string.push('\n');
    }

    console.log(...string);
}

printPrettyBoard(solve("1-58-2----9--764-52--4--819-19--73-6762-83-9-----61-5---76---3-43--2-5-16--3-89--"));
printPrettyBoard(solve("--5-3--819-285--6-6----4-5---74-283-34976---5--83--49-15--87--2-9----6---26-495-3"));
printPrettyBoard(solve("29-5----77-----4----4738-129-2--3-648---5--7-5---672--3-9--4--5----8-7---87--51-9"));
printPrettyBoard(solve("-8--2-----4-5--32--2-3-9-466---9---4---64-5-1134-5-7--36---4--24-723-6-----7--45-"));
printPrettyBoard(solve("6-873----2-----46-----6482--8---57-19--618--4-31----8-86-2---39-5----1--1--4562--"));
printPrettyBoard(solve("---6891--8------2915------84-3----5-2----5----9-24-8-1-847--91-5------6--6-41----"));
printPrettyBoard(solve("-3-5--8-45-42---1---8--9---79-8-61-3-----54---5------78-----7-2---7-46--61-3--5--"));
printPrettyBoard(solve("-96-4---11---6---45-481-39---795--43-3--8----4-5-23-18-1-63--59-59-7-83---359---7"));
printPrettyBoard(solve("----754----------8-8-19----3----1-6--------34----6817-2-4---6-39------2-53-2-----"));
printPrettyBoard(solve("3---------5-7-3--8----28-7-7------43-----------39-41-54--3--8--1---4----968---2--"));
printPrettyBoard(solve("3-26-9--55--73----------9-----94----------1-9----57-6---85----6--------3-19-82-4-"));
printPrettyBoard(solve("-2-5----48-5--------48-9-2------5-73-9-----6-25-9------3-6-18--------4-71----4-9-"));
printPrettyBoard(solve("--7--8------2---6-65--79----7----3-5-83---67-2-1----8----71--38-2---5------4--2--"));
printPrettyBoard(solve("----------2-65-------18--4--9----6-4-3---57-------------------73------9----------"));
printPrettyBoard(solve("---------------------------------------------------------------------------------"));
