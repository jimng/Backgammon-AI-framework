#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include "curses.h"

#include "Board.cpp"
#include "Random.cpp"
#include "Human.cpp"
#include "Minimax.cpp"

WINDOW* window;
Player* firstPlayer = NULL;
Player* secondPlayer = NULL;
char bd[20][20];

void writeLog(std::string content){
    std::ofstream out("log.txt", std::ofstream::app);
    out << content << std::endl;
    out.close();
}

void initGame(){
    window = initscr();
    keypad(stdscr,TRUE);
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            bd[i][j] = ' ';
        }
    }
}

void endGame(){
    delwin(window);
    endwin();
    refresh();
}

void render(){
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
                ch = bd[i / 2][j / 4];
            }
            mvaddch(i + 1, j + 1, ch);
        }
    }
    refresh();
    move(Board::cursorY * 2 + 2, Board::cursorX * 4 + 3);
}

Player* getClass(char* name){
    if (strcmp(name, "Random") == 0){
        return new Random();
    }else if (strcmp(name, "Minimax") == 0){
        return new Minimax();
    }else if (strcmp(name, "Human") == 0){
        return new Human();
    }
    return NULL;
}

int main(int argc, char **argv){

    int gameResult = -1;

    firstPlayer = getClass(argv[1]);
    secondPlayer = getClass(argv[2]);

    initGame();
    render();

    bool activePlayerNum = 0;
    Player* players[2] = {firstPlayer, secondPlayer};
    while((gameResult = Board::determineWinner(bd)) == -1){
        Player* activePlayer = players[activePlayerNum];
        int selectedRow = 0, selectedColumn = 0;
        do{
            activePlayer->getNextStep(bd, Board::charSet[activePlayerNum], &selectedRow, &selectedColumn);
        }while(!Board::isMoveValid(bd, selectedRow, selectedColumn));
        bd[selectedRow][selectedColumn] = Board::charSet[activePlayerNum];
        activePlayerNum = !activePlayerNum;
        render();
        usleep(50000);
    }

    Board::highlightWinning(bd);
    move(1, 1);
    getch();
    endGame();

    if (gameResult == 0){
        printf("Player 1 (%s) wins for this game\n", argv[1]);
    }else if (gameResult == 1){
        printf("Player 2 (%s) wins for this game\n", argv[2]);
    }else{
        printf("Draw\n");
    }

    return 0;
}
