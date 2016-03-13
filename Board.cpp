#include <vector>

#ifndef BOARD
#define BOARD
class Board{
    public:
        int h;
        int w;
        // Length for winning
        int l;
        // 0 = unfilled, 1 = Player1 filled, 2 = player2 filled
        std::vector< std::vector<unsigned char> > board;
        bool isHighlight;
        std::vector< std::vector<bool> > highlightBitmap;

        Board(int, int, int);
        // 0 = invalid, 1 = valid
        bool fill(int, int, int);
        // 0 = Still playing, 1 = Player1, 2 = Player2, 3 = Draw
        int determineWinner();
    private:

        bool isMoveValid(int, int);
        bool findWinningVector(int*, int*, int*, int*);
        int isWinningVector(int, int, int, int);
        bool isFull();
};

/********* Public *********/

Board::Board(int h, int w, int l) : h(h), w(w), l(l){
    this->board = std::vector< std::vector<unsigned char> >(h, std::vector<unsigned char>(w, (unsigned char) 0));
    this->isHighlight = false;
}

bool Board::fill(int row, int column, int playerNum){
    if (isMoveValid(row, column)){
        this->board[row][column] = (unsigned char) playerNum;
        return true;
    }else{
        return false;
    }
}

int Board::determineWinner(){
    int row, column, dy, dx;
    if (this->findWinningVector(&row, &column, &dy, &dx)){
        // highlight
        this->isHighlight = true;
        this->highlightBitmap = std::vector< std::vector<bool> >(h, std::vector<bool>(w, 0));
        for (int k = 0; k < this->l; k++){
            this->highlightBitmap[row + dy * k][column + dx * k] = true;
        }

        return this->board[row][column];
    }else if (this->isFull()){
        return 3;
    }else{
        return 0;
    }
}

/********* Private *********/

bool Board::isMoveValid(int row, int column){
    if (this->board[row][column] != 0){
        return false;
    }else{
        return true;
    }
}

bool Board::findWinningVector(int* row, int *column, int *dy, int *dx){
    for (int i = 0; i < this->h; i++){
        for (int j = 0; j < this->w; j++){
            *row = i;
            *column = j;
            // Horizontal
            if (j < this->w - this->l + 1){
                *dy = 0;
                *dx = 1;
                int winner = this->isWinningVector(*row, *column, *dy, *dx);
                if (winner != 0){
                    return true;
                }
            }
            // Vertical
            if (i < this->h - this->l + 1){
                *dy = 1;
                *dx = 0;
                int winner = this->isWinningVector(*row, *column, *dy, *dx);
                if (winner != 0){
                    return true;
                }
            }
            // Diagonal (\)
            if (i < this->h - this->l + 1 && j < this->w - this->l + 1){
                *dy = 1;
                *dx = 1;
                int winner = this->isWinningVector(*row, *column, *dy, *dx);
                if (winner != 0){
                    return true;
                }
            }
            // Diagnoal (/)
            if (i > this->l - 2 && j < this->w - this->l + 1){
                *dy = -1;
                *dx = 1;
                int winner = this->isWinningVector(*row, *column, *dy, *dx);
                if (winner != 0){
                    return true;
                }
            }
        }
    }
    return false;
}

int Board::isWinningVector(int row, int column, int dy, int dx){
    if (this->board[row][column] == 0){
        return 0;
    }
    for (int k = 1; k < this->l; k++){
        if (this->board[row + dy * k][column + dx * k] != this->board[row][column]){
            return 0;
        }
    }
    return this->board[row][column];
}

bool Board::isFull(){
    for (int i = 0; i < this->h; i++){
        for (int j = 0; j < this->w; j++){
            if (this->board[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}
#endif
