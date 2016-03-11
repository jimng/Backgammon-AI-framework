#include <vector>
#include <cstdlib>
#include "Player.cpp"

class Random:public Player{
    public:
        void getNextStep(char[][20], char, int*, int*);
    private:

};

void Random::getNextStep(char bd[][20], char sign, int* row, int* column){

    std::vector<int> availList;
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            if (bd[i][j] == ' '){
                availList.push_back(i * 20 + j);
            }
        }
    }
    int idx = rand() % availList.size();

    *row = availList[idx] / 20;
    *column = availList[idx] % 20;

}
