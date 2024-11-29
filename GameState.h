
#ifndef PROJECT4_GAMESTATE_H
#define PROJECT4_GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Toolbox.h"


class GameState {
    friend class Toolbox;
public:
    enum PlayStatus{WIN, LOSS, PLAYING};
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25,16), int _numberOfMines =50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
private:
    std::vector<std::vector<int>> board;
    PlayStatus status;
};


#endif //PROJECT4_GAMESTATE_H
