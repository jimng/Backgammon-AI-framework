#include <cstdio>
#include <cstring>
#include <unistd.h>

#include "Board.cpp"
#include "View.cpp"
#include "Random.cpp"
#include "Human.cpp"
#include "Minimax.cpp"

Player* getClass(char* name, View* view){
    if (strcmp(name, "Random") == 0){
        return new Random();
    }else if (strcmp(name, "Minimax") == 0){
        return new Minimax();
    }else if (strcmp(name, "Human") == 0){
        return new Human(view);
    }
    return NULL;
}

int main(int argc, char **argv){

    Board* board = new Board(20, 20, 5);
    View* view = new View();

    Player* firstPlayer = getClass(argv[1], view);
    Player* secondPlayer = getClass(argv[2], view);

    view->init();
    view->render(board);

    int gameResult = -1;
    int activePlayerNum = 1;
    Player* players[3] = {NULL, firstPlayer, secondPlayer};
    while((gameResult = board->determineWinner()) == 0){
        Player* activePlayer = players[activePlayerNum];
        int selectedRow = 0, selectedColumn = 0;
        do{
            view->render(board);
            activePlayer->getNextStep(board, activePlayerNum, &selectedRow, &selectedColumn);
        }while(!board->fill(selectedRow, selectedColumn, activePlayerNum));
        activePlayerNum = 3 - activePlayerNum;
        view->render(board);
        usleep(50000);
    }

    view->render(board);
    getch();
    view->end();

    if (gameResult == 1){
        printf("Player 1 (%s) wins for this game\n", argv[1]);
    }else if (gameResult == 2){
        printf("Player 2 (%s) wins for this game\n", argv[2]);
    }else{
        printf("Draw\n");
    }

    return 0;
}
