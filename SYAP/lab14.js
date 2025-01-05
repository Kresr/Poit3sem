class Sudoku {
    constructor() {
        this.initialBoard = Array.from({ length: 9 }, () => Array(9).fill(0));
        this.board = this.cloneBoard(this.initialBoard);
    }

    // Клонируем игровое поле
    cloneBoard(board) {
        return board.map(row => [...row]);
    }

    // Сбрасываем игровое поле до начального состояния
    resetBoard() {
        this.board = this.cloneBoard(this.initialBoard);
    }

    // Проверка строки на дубликаты
    checkRow(row) {
        const seen = new Set();
        for (let col = 0; col < 9; col++) {
            const num = this.board[row][col];
            if (num !== 0) {
                if (seen.has(num)) return false;
                seen.add(num);
            }
        }
        return true;
    }

    // Проверка столбца на дубликаты
    checkColumn(col) {
        const seen = new Set();
        for (let row = 0; row < 9; row++) {
            const num = this.board[row][col];
            if (num !== 0) {
                if (seen.has(num)) return false;
                seen.add(num);
            }
        }
        return true;
    }

    // Проверка квадрата 3x3 на дубликаты
    checkSquare(row, col) {
        const seen = new Set();
        const startRow = row - (row % 3);
        const startCol = col - (col % 3);
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                const num = this.board[startRow + i][startCol + j];
                if (num !== 0) {
                    if (seen.has(num)) return false;
                    seen.add(num);
                }
            }
        }
        return true;
    }

    // Проверка всего игрового поля
    checkBoard() {
        for (let i = 0; i < 9; i++) {
            if (!this.checkRow(i) || !this.checkColumn(i)) return false;
        }
        for (let row = 0; row < 9; row += 3) {
            for (let col = 0; col < 9; col += 3) {
                if (!this.checkSquare(row, col)) return false;
            }
        }
        return true;
    }

    // Генерация полного корректного решения
    generateSolution() {
        const fillBoard = (row, col) => {
            if (col === 9) {
                col = 0;
                row++;
                if (row === 9) return true;
            }

            const numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9].sort(() => Math.random() - 0.5);

            for (const num of numbers) {
                if (this.isValidPlacement(row, col, num)) {
                    this.board[row][col] = num;
                    if (fillBoard(row, col + 1)) return true;
                    this.board[row][col] = 0;
                }
            }

            return false;
        };

        this.resetBoard();
        fillBoard(0, 0);
    }

    // Проверка, можно ли разместить число в клетке
    isValidPlacement(row, col, num) {
        for (let i = 0; i < 9; i++) {
            if (this.board[row][i] === num || this.board[i][col] === num) return false;
        }

        const startRow = row - (row % 3);
        const startCol = col - (col % 3);
        for (let i = 0; i < 3; i++) {
            for (let j = 0; j < 3; j++) {
                if (this.board[startRow + i][startCol + j] === num) return false;
            }
        }

        return true;
    }

    // Генерация стартового поля с подсказками
    generateInitialBoard(hintCount = 30) {
        this.generateSolution(); // Сначала генерируем полное решение
        const hints = new Set();

        // Добавляем случайные подсказки
        while (hints.size < hintCount) {
            const row = Math.floor(Math.random() * 9);
            const col = Math.floor(Math.random() * 9);
            hints.add(`${row}-${col}`);
        }

        this.initialBoard = this.cloneBoard(this.board);
        for (let i = 0; i < 9; i++) {
            for (let j = 0; j < 9; j++) {
                if (!hints.has(`${i}-${j}`)) {
                    this.initialBoard[i][j] = 0; // Очищаем клетки, которые не являются подсказками
                }
            }
        }

        this.board = this.cloneBoard(this.initialBoard); // Устанавливаем начальное состояние
    }

    // Решение текущего поля с учетом заполненных ячеек
    generateSolutionForCurrentBoard() {
        const fillBoard = (row, col) => {
            if (col === 9) {
                col = 0;
                row++;
                if (row === 9) return true;
            }

            if (this.board[row][col] !== 0) {
                return fillBoard(row, col + 1);
            }

            const numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9].sort(() => Math.random() - 0.5);

            for (const num of numbers) {
                if (this.isValidPlacement(row, col, num)) {
                    this.board[row][col] = num;
                    if (fillBoard(row, col + 1)) return true;
                    this.board[row][col] = 0;
                }
            }

            return false;
        };

        fillBoard(0, 0);
    }
}

const sudoku = new Sudoku();
const boardElement = document.getElementById('board');

// Создание интерфейса игрового поля
function createBoard() {
    boardElement.innerHTML = '';
    for (let i = 0; i < 9; i++) {
        for (let j = 0; j < 9; j++) {
            const cell = document.createElement('input');
            cell.type = 'text';
            cell.maxLength = 1;
            cell.classList.add('cell');
            cell.dataset.row = i;
            cell.dataset.col = j;
            boardElement.appendChild(cell);
        }
    }
}

// Обновление интерфейса с данными из модели
function updateBoard() {
    document.querySelectorAll('.cell').forEach(cell => {
        const row = +cell.dataset.row;
        const col = +cell.dataset.col;
        const value = sudoku.board[row][col];
        const initialValue = sudoku.initialBoard[row][col];

        cell.value = value === 0 ? '' : value; // Пустые клетки остаются пустыми
        cell.classList.remove('error', 'valid'); // Сбрасываем подсветку ошибок

        // Блокируем предустановленные значения
        if (initialValue !== 0) {
            cell.setAttribute('disabled', 'true');
        } else {
            cell.removeAttribute('disabled');
        }
    });
}

// Обновление модели с данными из интерфейса
function updateModel() {
    document.querySelectorAll('.cell').forEach(cell => {
        const row = +cell.dataset.row;
        const col = +cell.dataset.col;
        const value = parseInt(cell.value, 10);
        sudoku.board[row][col] = isNaN(value) ? 0 : value;
    });
}

// Подсветка ошибок в интерфейсе
function highlightErrors() {
    document.querySelectorAll('.cell').forEach(cell => {
        const row = +cell.dataset.row;
        const col = +cell.dataset.col;
        cell.classList.remove('error');
        if (!sudoku.checkRow(row) || !sudoku.checkColumn(col) || !sudoku.checkSquare(row, col)) {
            cell.classList.add('error');
        }
    });
}

// Обработчики кнопок

// Новая игра
document.getElementById('new-game').addEventListener('click', () => {
    sudoku.generateInitialBoard(); // Генерация стартового поля
    updateBoard(); // Обновление интерфейса
});

// Проверить поле
document.getElementById('check-board').addEventListener('click', () => {
    updateModel(); // Синхронизация модели
    if (sudoku.checkBoard()) {
        document.querySelectorAll('.cell').forEach(cell => cell.classList.add('valid'));
    } else {
        highlightErrors();
    }
});

// Решить поле
document.getElementById('solve-board').addEventListener('click', () => {
    updateModel(); // Синхронизация модели
    sudoku.generateSolutionForCurrentBoard(); // Решение для незаполненных ячеек
    updateBoard(); // Обновление интерфейса
});

// Инициализация игры
createBoard();
updateBoard();
