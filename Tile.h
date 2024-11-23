
#ifndef PROJECT4_TILE_H
#define PROJECT4_TILE_H
#include <SFML/Graphics.hpp>

class Tile {
public:
    enum State{REVEALED, HIDDEN, FLAGGED, EXPLODED};
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    State getState();
    std::array<Tile*, 8>& getNeighbors();
    void setState(State _state);
    void setNeighbors(std::array<Tile*, 8> _neighbors);
    void onClickLeft();
    void onClickRight();
    void draw();
    void revealNeighbors();
};


#endif //PROJECT4_TILE_H
