#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>

#include "Board.cpp"
#include "Random.cpp"
#include "Human.cpp"
#include "Minimax.cpp"

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

    Player* firstPlayer = getClass(argv[1]);
    Player* secondPlayer = getClass(argv[2]);

    int gameResult = -1;

    Board::initGame();
    Board::render();

    bool activePlayerNum = 0;
    Player* players[2] = {firstPlayer, secondPlayer};
    while((gameResult = Board::determineWinner()) == -1){
        Player* activePlayer = players[activePlayerNum];
        int selectedRow = 0, selectedColumn = 0;
        do{
            activePlayer->getNextStep(Board::bd, Board::charSet[activePlayerNum], &selectedRow, &selectedColumn);
        }while(!Board::isMoveValid(selectedRow, selectedColumn));
        Board::fill(selectedRow, selectedColumn, activePlayerNum);
        activePlayerNum = !activePlayerNum;
        Board::render();
        usleep(50000);
    }

    Board::highlightWinning();
    move(1, 1);
    getch();
    Board::endGame();

    if (gameResult == 0){
        printf("Player 1 (%s) wins for this game\n", argv[1]);
    }else if (gameResult == 1){
        printf("Player 2 (%s) wins for this game\n", argv[2]);
    }else{
        printf("Draw\n");
    }

    return 0;
}
