
#ifndef PROJECT4_TILE_H
#define PROJECT4_TILE_H
#include <SFML/Graphics.hpp>
#include "Toolbox.h"

class Tile {
    friend class Toolbox;
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
private:
    sf::Vector2f pos;
    State state;
    std::array<Tile*,8> neighbors;
    sf::Sprite sprite;
    static sf::Texture tile_hidden_texture;
    static sf::Texture tile_revealed_texture;
    static sf::Texture tile_flagged_texture;
    static sf::Texture tile_bomb_texture;
};


#endif //PROJECT4_TILE_H
