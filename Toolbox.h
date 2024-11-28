//
// Created by benad on 11/21/2024.
//

#ifndef PROJECT4_TOOLBOX_H
#define PROJECT4_TOOLBOX_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include "Tile.h";



class Toolbox {
    friend class GameState;
public:
    sf::RenderWindow window;
    GameState *gameState;
    Button *debugButton;
    Button *newGameButton;
    Button *testButton1;
    Button *testButton2;
    static Toolbox &getInstance();

private:
    Toolbox();
};


#endif //PROJECT4_TOOLBOX_H
