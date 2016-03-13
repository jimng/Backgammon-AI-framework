#include <algorithm>
#include "Player.cpp"

#ifndef MINIMAX
#define MINIMAX
class Minimax:public Player{
    public:
        Minimax();
        void getNextStep(Board*, int, int*, int*);

    private:
        static const int INF = 1 << 30;
        int maxDepth;
        int scoreVector[5];

        int minimax(Board*, int, int, int, int, bool, int*, int*);
        int computeScore(Board*, int);
        int computeVectorScore(Board*, int, int, int, int, int);
};

/********** Public **********/

Minimax::Minimax(){
    this->maxDepth = 2;
    int scoreVector[5] = {1, 5, 25, 500, 10000};
    memcpy(this->scoreVector, scoreVector, sizeof(scoreVector));
}

void Minimax::getNextStep(Board* board, int playerNum, int* row, int* column){
    this->minimax(board, playerNum, 0, -Minimax::INF, Minimax::INF, true, row, column);
}

/********** Private **********/

int Minimax::minimax(Board* board, int playerNum, int depth, int alpha, int beta, bool isMaximize, int *bestY, int *bestX){
    int dumpX, dumpY;
    if (depth >= this->maxDepth){
        return this->computeScore(board, playerNum);
    }
    Board* newBoard = new Board(*board);
    if (isMaximize){
        int v = -Minimax::INF;
        for (int i = 0; i < board->h; i++){
            for (int j = 0; j < board->w; j++){
                if (board->board[i][j] == 0){
                    newBoard->board[i][j] = playerNum;
                    int newV = this->minimax(newBoard, playerNum, depth + 1, alpha, beta, false, &dumpX, &dumpY);
                    if (newV > v){
                        *bestY = i; *bestX = j;
                        v = newV;
                    }
                    alpha = std::max(alpha, v);
                    newBoard->board[i][j] = 0;
                    if (beta <= alpha) break;
                }
            }
        }
        return v;
    }else{
        int v = Minimax::INF;
        for (int i = 0; i < board->h; i++){
            for (int j = 0; j < board->w; j++){
                if (board->board[i][j] == 0){
                    newBoard->board[i][j] = 3 - playerNum;
                    int newV = this->minimax(newBoard, playerNum, depth + 1, alpha, beta, true, &dumpX, &dumpY);
                    if (newV < v){
                        *bestY = i; *bestX = j;
                        v = newV;
                    }
                    beta = std::min(beta, v);
                    newBoard->board[i][j] = 0;
                    if (beta <= alpha) break;
                }
            }
        }
        return v;
    }
}

int Minimax::computeScore(Board* board, int playerNum){
    int totalScore = 0;
    for (int i = 0; i < board->h; i++){
        for (int j = 0; j < board->w; j++){
            totalScore += this->computeVectorScore(board, playerNum, i, j, 0, 1);
            totalScore += this->computeVectorScore(board, playerNum, i, j, 1, 0);
            totalScore += this->computeVectorScore(board, playerNum, i, j, 1, 1);
            totalScore += this->computeVectorScore(board, playerNum, i, j, -1, 1);
        }
    }
    return totalScore;
}

int Minimax::computeVectorScore(Board* board, int playerNum, int row, int column, int dy, int dx){
    int countSelf = 0, countOpponent = 0;
    for (int k = 0; k < board->l; k++){
        int ny = row + dy * k;
        int nx = column + dx * k;
        if (ny >= 0 && ny < board->h && nx >= 0 && nx < board->w){
            if (playerNum == board->board[ny][nx]) countSelf++;
            else if (3 - playerNum == board->board[ny][nx]) countOpponent++;
        }else{
            return 0;
        }
    }
    if (countSelf > 0 && countOpponent > 0) return 0;
    else if (countSelf > 0 && countOpponent == 0) return this->scoreVector[countSelf - 1];
    else if (countSelf == 0 && countOpponent > 0) return -this->scoreVector[countOpponent - 1];
    else return 0;
}
#endif
