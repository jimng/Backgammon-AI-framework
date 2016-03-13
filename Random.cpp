#include <vector>
#include <cstdlib>
#include "Player.cpp"

#ifndef RANDOM
#define RANDOM
class Random:public Player{
    public:
        void getNextStep(Board*, int, int*, int*);
    private:

};

void Random::getNextStep(Board* board, int playerNum, int* row, int* column){

    std::vector<int> availList;
    for (int i = 0; i < board->h; i++){
        for (int j = 0; j < board->w; j++){
            if (board->board[i][j] == 0){
                availList.push_back(i * board->w + j);
            }
        }
    }
    int idx = rand() % availList.size();

    *row = availList[idx] / board->w;
    *column = availList[idx] % board->w;

}
#endif
