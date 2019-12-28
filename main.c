#include <stdio.h>
#include <time.h>

/**
 * Author: Zino Holwerda
 * March 4, 2018
 * This is a simple program to solve a sudoku and falls under the GNU Public license.
 */

typedef struct Cell {
    int stat;
    int value;
} Cell;

int done=0;

int checkVertical(Cell (*sudoku)[9][9], int x, int y, int cur) {
    for (int i = 0; i < 9; ++i) {
        if(i != x && cur == (*sudoku)[y][i].value)
            return 0;
    }
    return 1;
}

int checkHorizontal(Cell (*sudoku)[9][9], int x, int y, int cur) {
    for (int i = 0; i < 9; ++i) {
        if(i != y && cur == (*sudoku)[i][x].value)
            return 0;
    }
    return 1;
}

int checkSquare(Cell (*sudoku)[9][9], int x, int y) {
    int squareX = x / 3, squareY = y / 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(squareX*3+i == x && squareY*3+j == y) continue;
            if((*sudoku)[y][x].value == (*sudoku)[squareY*3+j][squareX*3+i].value) {
                return 0;
            }
        }
    }
    return 1;
}

int checker(Cell (*sudoku)[9][9], int x, int y) {
    return (checkSquare(sudoku, x, y) && checkHorizontal(sudoku, x, y, (*sudoku)[y][x].value)
            && checkVertical(sudoku, x, y, (*sudoku)[y][x].value));
}

void printSudoku(Cell (*sudoku)[9][9]) {
    printf("\n");
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            printf("%d ", (*sudoku)[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}

void solver(Cell (*sudoku)[9][9], int x, int y) {
    if(done) return;
    if (y == 9) {
        if(checker(sudoku, 8, 8)) {
            done = 1;
            printSudoku(sudoku);
        }
        return;
    }
    int value=1;
    while (value < 10) {
        if((*sudoku)[y][x].stat != 1) {
            (*sudoku)[y][x].value=value;
        } else {
            value = 9;
        }
        if (checker(sudoku, x, y)) {
            if (x < 8) {
                solver(sudoku, x + 1, y);
            } else {
                solver(sudoku, 0, y + 1);
            }
        }
        ++value;
    }
    if((*sudoku)[y][x].stat != 1) {
        (*sudoku)[y][x].value=0;
    }
}

int main() {
    Cell sudoku[9][9];
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            sudoku[i][j].value = 0;
            sudoku[i][j].stat = 0;
        }
    }
    int cnt=0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int temp;
            scanf("%d", &temp);
            sudoku[i][j].value = temp;
            if (temp > 0) {
                sudoku[i][j].stat = 1;
            }
            ++cnt;
        }
        getchar();
    }
    if(cnt > 17) {
        clock_t begin = clock();
        solver(&sudoku, 0, 0);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Solved sudoku in: %.3lf sec.\n", time_spent);
    } else {
        printf("Not solvable\n");
    }
    return 0;
}
