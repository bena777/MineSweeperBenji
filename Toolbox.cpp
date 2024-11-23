
#include "Toolbox.h"
#include <SFML/Graphics.hpp>

Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}

Toolbox::Toolbox(){
    window.create(sf::VideoMode(800,600), "P4- Minesweeper, Ben Adelman");

}
