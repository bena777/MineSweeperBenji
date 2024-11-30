
#include "Tile.h"
#include "GameState.h"
#include "Toolbox.h"
#include <iostream>
sf::Texture Tile::tile_hidden_texture;
sf::Texture Tile::tile_revealed_texture;
sf::Texture Tile::tile_flagged_texture;
sf::Texture Tile::tile_bomb_texture;


Tile::Tile(sf::Vector2f position) {
    pos = position;
    tile_hidden_texture.loadFromFile("images/tile_hidden.png");
    tile_revealed_texture.loadFromFile("images/tile_revealed.png");
    tile_flagged_texture.loadFromFile("images/flag.png");
    tile_bomb_texture.loadFromFile("images/mine.png");
    sprite.setTexture(tile_hidden_texture);
    sprite.setPosition(position);
    state = HIDDEN;
}
sf::Vector2f Tile::getLocation() {
    return pos;
}
void Tile::setState(State _state) {
    state = _state;
    if(state == HIDDEN) {
        sprite.setTexture(tile_hidden_texture);
    } else if(state == REVEALED) {
        sprite.setTexture(tile_revealed_texture);
    } else if(state == FLAGGED) {
        sprite.setTexture(tile_flagged_texture);
    } else if(state == EXPLODED) {
        sprite.setTexture(tile_bomb_texture);
    }
}
void Tile::draw() {
    Toolbox::getInstance().window.draw(sprite);
}
Tile::State Tile::getState() {
    return state;
}
std::array<Tile *, 8> &Tile::getNeighbors() {
    return neighbors;
}



void Tile::onClickLeft() {
    if(state == HIDDEN) {
        state = REVEALED;
        //revealNeighbors();
    }
}
void Tile::onClickRight() {
    if(state == FLAGGED) {
        this->setState(HIDDEN);
    } else if (state == HIDDEN) {
        this->setState(FLAGGED);
    }
}


void Tile::setNeighbors(std::array<Tile *, 8> _neighbors) {
    neighbors = _neighbors;
}
void Tile::revealNeighbors() {
    if (this!=nullptr) {
        if (this->getState() != HIDDEN) {
            return;
        }
        this->setState(REVEALED);
        int mineCount = 0;
        for (Tile* neighbor : neighbors) {
            if (neighbor != nullptr && neighbor->bomb == 1) {
                mineCount++;
            }
        }
        if (mineCount == 0) {
            for (Tile* neighbor : neighbors) {
                if (neighbor != nullptr && neighbor->getState() == HIDDEN) {
                    neighbor->revealNeighbors();
                }
            }
        }
    }
}
