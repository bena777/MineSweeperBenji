
#ifndef PROJECT4_GAMESTATE_H
#define PROJECT4_GAMESTATE_H
#include <SFML/Graphics.hpp>


class GameState {
public:
    enum PlayStatus{WIN, LOSS, PLAYING};
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25,16), int _numberOfMines =50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTitle(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
};


#endif //PROJECT4_GAMESTATE_H
