//
// Created by benad on 11/21/2024.
//

#ifndef PROJECT4_TOOLBOX_H
#define PROJECT4_TOOLBOX_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "GameState.h"
#include "Tile.h"


class GameState;
class Toolbox {
    friend class GameState;
    friend class Tile;
public:
    sf::RenderWindow window;
    GameState *gameState;
    Button *debugButton;
    Button *newGameButton;
    Button *testButton1;
    Button *testButton2;
    std::vector<std::vector<int>> board;
    static Toolbox &getInstance();
    std::vector<std::vector<Tile>> tiles;
    std::vector<std::vector<int>> bomb_neighbors;
    void new_button();
    void debug_button();
    void test_1_button();
    void test_2_button();
    bool current;
    sf::Sprite new_game_sprite;
    sf::Texture new_game;
    sf::Sprite new_game_good_sprite;
    sf::Sprite new_game_bad_sprite;
    int flags = 0;
    void bombom(int row, int col);
    void displayCounter(sf::RenderWindow& window, int number, const sf::Texture& texture, float startX, float startY);
    sf::Texture digitsTexture;
    bool debug = false;
    void checkWin();
private:
    Toolbox();
};


#endif //PROJECT4_TOOLBOX_H
