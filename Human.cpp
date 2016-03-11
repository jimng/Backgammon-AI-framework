#include "curses.h"
#include "Player.cpp"

class Human:public Player{
    public:
        void getNextStep(char[][20], char, int*, int*);
    private:

};

void Human::getNextStep(char bd[][20], char sign, int* row, int* column){
    move(Board::cursorY * 2 + 2, Board::cursorX * 4 + 3);
    int ch;
    do{
        ch=getch();
        if (ch == KEY_UP){
            if (Board::cursorY > 0) Board::cursorY--;
        }else if (ch == KEY_DOWN){
            if (Board::cursorY < 19) Board::cursorY++;
        }else if (ch == KEY_LEFT){
            if (Board::cursorX > 0) Board::cursorX--;
        }else if (ch == KEY_RIGHT){
            if (Board::cursorX < 19) Board::cursorX++;
        }
        move(Board::cursorY * 2 + 2, Board::cursorX * 4 + 3);
    }while(ch != '\n');
    *row = Board::cursorY;
    *column = Board::cursorX;
}
