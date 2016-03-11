#include "curses.h"

#ifndef BOARD
#define BOARD
class Board{
    public:
        const static char charSet[2];
        static int cursorX;
        static int cursorY;

        static bool isMoveValid(char[][20], int, int);
        static int determineWinner(char[][20]);

        static void highlightWinning(char[][20]);
    private:
        static bool findWinningVector(char [][20], int*, int*, int*, int*);
        static int isWinningVector(char[][20], int, int, int, int);
        static bool isFull(char[][20]);

        static void highlightVector(char[][20], int, int, int, int);
};

/********* Public *********/

const char Board::charSet[2] = {'O', 'X'};
int Board::cursorX = 0;
int Board::cursorY = 0;

bool Board::isMoveValid(char bd[][20], int row, int column){
    if (bd[row][column] != ' ') return false;
    else return true;
}

int Board::determineWinner(char bd[][20]){
    int row, column, dy, dx;
    if (Board::findWinningVector(bd, &row, &column, &dy, &dx)){
        if (bd[row][column] == charSet[0]) return 0;
        else return 1;
    }
    if (Board::isFull(bd)) return 2;
    else return -1;
}

void Board::highlightWinning(char bd[][20]){
    int row, column, dy, dx;
    Board::findWinningVector(bd, &row, &column, &dy, &dx);
    Board::highlightVector(bd, row, column, dy, dx);
}

/********* Private *********/

bool Board::findWinningVector(char bd[][20], int* row, int *column, int *dy, int *dx){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            *row = i;
            *column = j;
            // Horizontal
            if (j < 16){
                *dy = 0;
                *dx = 1;
                int winner = Board::isWinningVector(bd, *row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
            // Vertical
            if (i < 16){
                *dy = 1;
                *dx = 0;
                int winner = Board::isWinningVector(bd, *row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
            // Diagonal (\)
            if (i < 16 && j < 16){
                *dy = 1;
                *dx = 1;
                int winner = Board::isWinningVector(bd, *row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
            // Diagnoal (/)
            if (i > 3 && j < 16){
                *dy = -1;
                *dx = 1;
                int winner = Board::isWinningVector(bd, *row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
        }
    }
    return false;
}

int Board::isWinningVector(char bd[][20], int row, int column, int dy, int dx){
    if (bd[row][column] == ' ') return -1;
    for (int k = 1; k < 5; k++){
        if (bd[row + dy * k][column + dx * k] != bd[row][column]) return -1;
    }
    if (bd[row][column] == charSet[0]) return 0;
    else return 1;
}

bool Board::isFull(char bd[][20]){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            if (bd[i][j] == ' ') return false;
        }
    }
    return true;
}

void Board::highlightVector(char bd[][20], int row, int column, int dy, int dx){
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (int k = 0; k < 5; k++){
        mvaddch((row + dy * k) * 2 + 2, (column + dx * k) * 4 + 3, bd[row][column]);
    }
    attroff(COLOR_PAIR(1));
}
#endif
