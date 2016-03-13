#include "Player.cpp"

#ifndef HUMAN
#define HUMAN
class Human:public Player{
    public:
        View* view;

        Human(View*);
        void getNextStep(Board*, int, int*, int*);
    private:

};

/********** Public **********/

Human::Human(View* view) : view(view){
}

void Human::getNextStep(Board* board, int playerNum, int* row, int* column){
    int ch;
    do{
        ch=getch();
        if (ch == KEY_UP){
            view->moveCursorUp(board);
        }else if (ch == KEY_DOWN){
            view->moveCursorDown(board);
        }else if (ch == KEY_LEFT){
            view->moveCursorLeft(board);
        }else if (ch == KEY_RIGHT){
            view->moveCursorRight(board);
        }
    }while(ch != '\n');
    view->getCursorPosition(row, column);
}

/********** Private **********/
#endif
