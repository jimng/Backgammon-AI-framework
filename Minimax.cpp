#include <algorithm>
#include "Player.cpp"

class Minimax:public Player{
    public:
        Minimax();
        void getNextStep(char[][20], char, int*, int*);

    private:
        static const int INF = 1 << 30;
        int maxDepth;
        int scoreVector[5];

        char anotherSign(char);
        int minimax(char[][20], char, int, int, int, bool, int*, int*);
        int computeScore(char[][20], char);
        int computeVectorScore(char[][20], char, int, int, int, int);
};

/********** Public **********/

Minimax::Minimax(){
    this->maxDepth = 2;
    int scoreVector[5] = {1, 5, 25, 500, 10000};
    memcpy(this->scoreVector, scoreVector, sizeof(scoreVector));
}

void Minimax::getNextStep(char bd[][20], char sign, int* row, int* column){
    this->minimax(bd, sign, 0, -Minimax::INF, Minimax::INF, true, row, column);
}

/********** Private **********/

char Minimax::anotherSign(char sign){
    return (sign == Board::charSet[0] ? Board::charSet[1] : Board::charSet[0]);
    return 'O';
}

int Minimax::minimax(char bd[][20], char sign, int depth, int alpha, int beta, bool isMaximize, int *bestY, int *bestX){
    int dumpX, dumpY;
    if (depth >= this->maxDepth){
        return this->computeScore(bd, sign);
    }
    char newBd[20][20];
    std::copy(&bd[0][0], &bd[0][0] + 400, &newBd[0][0]);
    if (isMaximize){
        int v = -Minimax::INF;
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 20; j++){
                if (bd[i][j] == ' '){
                    newBd[i][j] = sign;
                    int newV = this->minimax(newBd, sign, depth + 1, alpha, beta, false, &dumpX, &dumpY);
                    if (newV > v){
                        *bestY = i; *bestX = j;
                        v = newV;
                    }
                    alpha = std::max(alpha, v);
                    newBd[i][j] = bd[i][j];
                    if (beta <= alpha) break;
                }
            }
        }
        return v;
    }else{
        int v = Minimax::INF;
        for (int i = 0; i < 20; i++){
            for (int j = 0; j < 20; j++){
                if (bd[i][j] == ' '){
                    newBd[i][j] = this->anotherSign(sign);
                    int newV = this->minimax(newBd, sign, depth + 1, alpha, beta, true, &dumpX, &dumpY);
                    if (newV < v){
                        *bestY = i; *bestX = j;
                        v = newV;
                    }
                    beta = std::min(beta, v);
                    newBd[i][j] = bd[i][j];
                    if (beta <= alpha) break;
                }
            }
        }
        return v;
    }
}

int Minimax::computeScore(char bd[][20], char sign){
    int totalScore = 0;
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            totalScore += this->computeVectorScore(bd, sign, i, j, 0, 1);
            totalScore += this->computeVectorScore(bd, sign, i, j, 1, 0);
            totalScore += this->computeVectorScore(bd, sign, i, j, 1, 0);
            totalScore += this->computeVectorScore(bd, sign, i, j, -1, 1);
        }
    }
    return totalScore;
}

int Minimax::computeVectorScore(char bd[][20], char sign, int row, int column, int dy, int dx){
    int countSelf = 0, countOpponent = 0;
    for (int k = 0; k < 5; k++){
        int ny = row + dy * k;
        int nx = column + dx * k;
        if (ny >= 0 && ny < 20 && nx >= 0 && nx < 20){
            if (sign == bd[ny][nx]) countSelf++;
            else if (this->anotherSign(sign) == bd[ny][nx]) countOpponent++;
        }else{
            return 0;
        }
    }
    if (countSelf > 0 && countOpponent > 0) return 0;
    else if (countSelf > 0 && countOpponent == 0) return this->scoreVector[countSelf - 1];
    else if (countSelf == 0 && countOpponent > 0) return -this->scoreVector[countOpponent - 1];
    else return 0;
}
