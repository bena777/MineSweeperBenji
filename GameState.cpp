#include <fstream>
#include "GameState.h"
#include <vector>
#include <iostream>

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines){
    int mines_placed = 0;
    board.resize(_dimensions.x, std::vector<int>(_dimensions.y, 0));
    srand(time(NULL));
    while(mines_placed<_numberOfMines){
        int num = (rand() % _dimensions.x);
        int num2 = (rand() % _dimensions.y);
        if(board[num][num2] == 0) {
            board[num][num2] = 1;
            mines_placed++;
        }
    }
}
GameState::GameState(const char *filepath) {
    std::ifstream inStream(filepath);
    std::string w;
    int count = 0;
    std::string line;
    while (std::getline(inStream,line)) {
        std::vector<int> li;
        for (char c : line) {
            if (c == '0') {
                li.push_back(0);
            } else if (c == '1') {
                li.push_back(1);
            }
        }
        count++;
        board.push_back(li);
    }
}
int GameState::getMineCount() {
    int count = 0;
    for(int i=0; i<board.size(); i++) {
        for(int j=0; j<board[0].size(); j++) {
            if(board[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}
void GameState::setPlayStatus(PlayStatus _status) {
    status = _status;
}
GameState::PlayStatus GameState::getPlayStatus() {
    return status;
}