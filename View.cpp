#include <ncurses.h>

#ifndef VIEW
#define VIEW
class View{
    public:
        View();
        void init();
        void render(Board*);
        void end();

        void moveCursorUp(Board*);
        void moveCursorDown(Board*);
        void moveCursorLeft(Board*);
        void moveCursorRight(Board*);
        void getCursorPosition(int*, int*);

    private:
        WINDOW* window;
        char renderChar[3];
        int cursorX;
        int cursorY;

};

/********* Public *********/

View::View(){
    this->window = NULL;
    this->renderChar[0] = ' ';
    this->renderChar[1] = 'O';
    this->renderChar[2] = 'X';
    this->cursorX = 0;
    this->cursorY = 0;
}


void View::init(){
    this->window = initscr();
    keypad(stdscr,TRUE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

void View::render(Board* board){
    for (int i = 0; i < board->h * 2 + 1; i++){
        for (int j = 0; j < board->w * 4 + 1; j++){
            char ch = ' ';
            if (i % 2 != 0 && j % 4 == 2){
                ch = this->renderChar[board->board[i / 2][j / 4]];

                if (board->isHighlight && board->highlightBitmap[i / 2][j / 4]){
                    attron(COLOR_PAIR(1));
                    mvaddch(i + 1, j + 1, ch);
                    attroff(COLOR_PAIR(1));
                }else{
                    mvaddch(i + 1, j + 1, ch);
                }
            }else{
                if (i % 2 == 0 && j % 4 == 0){
                    ch = '+';
                }if (i % 2 == 0 && j % 4 == 2){
                    ch = '-';
                }else if (i % 2 != 0 && j % 4 == 0){
                    ch = '|';
                }
                mvaddch(i + 1, j + 1, ch);
            }
        }
    }
    refresh();
    move(this->cursorY * 2 + 2, this->cursorX * 4 + 3);
}

void View::end(){
    delwin(this->window);
    endwin();
    refresh();
}

void View::moveCursorUp(Board* board){
    if (this->cursorY > 0){
        this->cursorY--;
    }
    move(this->cursorY * 2 + 2, this->cursorX * 4 + 3);
    refresh();
}

void View::moveCursorDown(Board* board){
    if (this->cursorY < board->h - 1){
        this->cursorY++;
    }
    move(this->cursorY * 2 + 2, this->cursorX * 4 + 3);
    refresh();
}

void View::moveCursorLeft(Board* board){
    if (this->cursorX > 0){
        this->cursorX--;
    }
    move(this->cursorY * 2 + 2, this->cursorX * 4 + 3);
    refresh();
}

void View::moveCursorRight(Board* board){
    if (this->cursorX < board->w - 1){
        this->cursorX++;
    }
    move(this->cursorY * 2 + 2, this->cursorX * 4 + 3);
    refresh();
}

void View::getCursorPosition(int *row, int *column){
    *row = this->cursorY;
    *column = this->cursorX;
}

/********* Private *********/
#endif
