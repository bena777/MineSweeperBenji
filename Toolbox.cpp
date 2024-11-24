
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}

Toolbox::Toolbox(){
    window.create(sf::VideoMode(800,600), "P4- Minesweeper, Ben Adelman");
    while(window.isOpen()){
        sf::Event evnt;

        while(window.pollEvent(evnt)){
            switch(evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    std:: cout << evnt.mouseButton.x;
                    std::cout << evnt.mouseButton.y;

            }
            }
        }
    }
}
