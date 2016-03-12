#include <ncurses.h>

#ifndef BOARD
#define BOARD
class Board{
    public:
        static WINDOW* window;
        const static char charSet[2];
        static int cursorX;
        static int cursorY;
        static char bd[20][20];

        static void initGame();
        static void endGame();
        static void render();
        static void highlightWinning();

        static bool isMoveValid(int, int);
        static void fill(int, int, int);
        static int determineWinner();
    private:
        static bool findWinningVector(int*, int*, int*, int*);
        static int isWinningVector(int, int, int, int);
        static bool isFull();

        static void highlightVector(int, int, int, int);
};

/********* Public *********/

WINDOW* Board::window = NULL;
const char Board::charSet[2] = {'O', 'X'};
int Board::cursorX = 0;
int Board::cursorY = 0;
char Board::bd[20][20];

void Board::initGame(){
    Board::window = initscr();
    keypad(stdscr,TRUE);
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            Board::bd[i][j] = ' ';
        }
    }
}

void Board::endGame(){
    delwin(Board::window);
    endwin();
    refresh();
}

void Board::render(){
    for (int i = 0; i < 41; i++){
        for (int j = 0; j < 81; j++){
            char ch = ' ';
            if (i % 2 == 0 && j % 4 == 0){
                ch = '+';
            }else if (i % 2 == 0 && j % 4 == 2){
                ch = '-';
            }else if (i % 2 != 0 && j % 4 == 0){
                ch = '|';
            }else if (i % 2 != 0 && j % 4 == 2){
                ch = Board::bd[i / 2][j / 4];
            }
            mvaddch(i + 1, j + 1, ch);
        }
    }
    refresh();
    move(Board::cursorY * 2 + 2, Board::cursorX * 4 + 3);
}

void Board::highlightWinning(){
    int row, column, dy, dx;
    Board::findWinningVector(&row, &column, &dy, &dx);
    Board::highlightVector(row, column, dy, dx);
}

bool Board::isMoveValid(int row, int column){
    if (Board::bd[row][column] != ' ') return false;
    else return true;
}

void Board::fill(int row, int column, int playerNum){
    Board::bd[row][column] = Board::charSet[playerNum];
}

int Board::determineWinner(){
    int row, column, dy, dx;
    if (Board::findWinningVector(&row, &column, &dy, &dx)){
        if (Board::bd[row][column] == charSet[0]) return 0;
        else return 1;
    }
    if (Board::isFull()) return 2;
    else return -1;
}

/********* Private *********/

bool Board::findWinningVector(int* row, int *column, int *dy, int *dx){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            *row = i;
            *column = j;
            // Horizontal
            if (j < 16){
                *dy = 0;
                *dx = 1;
                int winner = Board::isWinningVector(*row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
            // Vertical
            if (i < 16){
                *dy = 1;
                *dx = 0;
                int winner = Board::isWinningVector(*row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
            // Diagonal (\)
            if (i < 16 && j < 16){
                *dy = 1;
                *dx = 1;
                int winner = Board::isWinningVector(*row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
            // Diagnoal (/)
            if (i > 3 && j < 16){
                *dy = -1;
                *dx = 1;
                int winner = Board::isWinningVector(*row, *column, *dy, *dx);
                if (winner != -1) return true;
            }
        }
    }
    return false;
}

int Board::isWinningVector(int row, int column, int dy, int dx){
    if (Board::bd[row][column] == ' ') return -1;
    for (int k = 1; k < 5; k++){
        if (Board::bd[row + dy * k][column + dx * k] != Board::bd[row][column]) return -1;
    }
    if (Board::bd[row][column] == charSet[0]) return 0;
    else return 1;
}

bool Board::isFull(){
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            if (Board::bd[i][j] == ' ') return false;
        }
    }
    return true;
}

void Board::highlightVector(int row, int column, int dy, int dx){
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for (int k = 0; k < 5; k++){
        mvaddch((row + dy * k) * 2 + 2, (column + dx * k) * 4 + 3, Board::bd[row][column]);
    }
    attroff(COLOR_PAIR(1));
}
#endif
