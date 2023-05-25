#include <stdio.h>
#include <stdlib.h>

#define N 9

void print(int **sudoku_board) {
    register int i, j;
    FILE* fout = fopen("test.out", "w");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            fprintf(fout, "%d ", sudoku_board[i][j]);
        }
        fprintf(fout, "\n");
    }

    fclose(fout);
}

int isValid(int **sudoku_board, int l, int c, int val) {
    register int k,q;

    for (k = 0; k < N; k++) {
        //verificare linie
        if (sudoku_board[l][k] == val)
            return 0;

        //verificare coloana
        if (sudoku_board[k][c] == val)
            return 0;
    }

    //verificare cadran
    int startL = l - l % 3;
    int startC = c - c % 3;

    for (k = 0; k < N/3; k++) {
        for (q = 0; q < N/3; q++) {
            if (sudoku_board[startL + k][startC + q] == val)
                return 0;
        }
    }
    return 1;
}

int solveSudoku(int **sudoku_board, int l, int c) {
    register int val;

    //finalul tablei de sudoku 
    if (l == N) {       
        print(sudoku_board);
        return 1;    
    }  
    //finalul randului
    else if (c == N) {   
        return solveSudoku(sudoku_board, l+1, 0);
    } 
    //numarul e deja scris
    else if (sudoku_board[l][c] != 0) {
        return solveSudoku(sudoku_board, l, c+1);
    } 
    else {
        for (val = 1; val <= N; val++) {
            //verufica daca valoarea poate fi adaugata in casuta libera
            if (isValid(sudoku_board, l, c, val)) {
                sudoku_board[l][c] = val;
                if (solveSudoku(sudoku_board, l, c+1))
                    return 1;
                sudoku_board[l][c] = 0;
            }
        }
        return 0;
    }
}

int main() {
    int **sudoku_board;
    register int i, j;

    //alocarea memoriei
    sudoku_board = (int**) malloc(N * sizeof(int*));
    for(i = 0; i < N; i++) {
        sudoku_board[i] = (int*) calloc(N, sizeof(int));
    }

    //citire
    FILE* fin = fopen("test.in", "r");
    for (i = 0; i < N; i++) {
         for (j = 0; j < N; j++) {
            fscanf(fin, "%d", &sudoku_board[i][j]);
        }
    }

    fclose(fin);

    solveSudoku(sudoku_board, 0, 0);

    //dealocarea memoriei
    for (i = 0; i < N; i++) {
        free(sudoku_board[i]);
    }
    free(sudoku_board);
    sudoku_board = NULL;

    return 0;
}