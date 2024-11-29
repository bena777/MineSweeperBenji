
#include "Toolbox.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Tile.h"
#include <vector>
#include "GameState.h"

Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}

Toolbox::Toolbox(){
    gameState = new GameState;
    board = gameState->board;
    int col = 25;
    int row = 16;
    int per_col = 800/col;
    int per_row = 510/row;
    for(int i=0; i<row; i++) {
        std::vector<Tile> cur;
        for(int j=0; j<col; j++) {
            sf::Vector2f tilePosition(j*32, i*32); //32 is length/height of tiles
            cur.emplace_back(tilePosition);
        }
        tiles.emplace_back(cur);
    }
    window.create(sf::VideoMode(800,600), "P4- Minesweeper, Ben Adelman");
    newGameButton = new Button(sf::Vector2f(400, 510), [this]() {std::cout << "new" <<std::endl;});
    debugButton = new Button(sf::Vector2f(528, 510), [this]() {}); //impliment functions later
    testButton1 = new Button(sf::Vector2f(592, 510), [this]() {});
    testButton2 = new Button(sf::Vector2f(656, 510), [this]() {});

    sf::Texture new_game;
    new_game.loadFromFile("images/face_happy.png");
    sf::Sprite new_game_sprite(new_game);
    newGameButton->setSprite(&new_game_sprite);

    sf::Texture debug;
    debug.loadFromFile("images/debug.png");
    sf::Sprite debug_sprite(debug);
    debugButton->setSprite(&debug_sprite);

    sf::Texture test_1;
    test_1.loadFromFile("images/test_1.png");
    sf::Sprite test1_sprite(test_1);
    testButton1->setSprite(&test1_sprite);

    sf::Texture test_2;
    test_2.loadFromFile("images/test_2.png");
    sf::Sprite test2_sprite(test_2);
    testButton2->setSprite(&test2_sprite);

    while(window.isOpen()){
        sf::Event evnt;
        while(window.pollEvent(evnt)){
            if(evnt.type == sf::Event::Closed) {
                window.close();
                break;
            }
            if(evnt.type == sf::Event::MouseButtonPressed){
                if(evnt.mouseButton.button == sf::Mouse::Left) {
                    if (newGameButton->getSprite()->getGlobalBounds().contains(evnt.mouseButton.x, evnt.mouseButton.y)) {
                        newGameButton->onClick();
                    }
                    if (debugButton->getSprite()->getGlobalBounds().contains(evnt.mouseButton.x, evnt.mouseButton.y)) {
                        debugButton->onClick();
                    }
                    if (testButton1->getSprite()->getGlobalBounds().contains(evnt.mouseButton.x, evnt.mouseButton.y)) {
                        testButton1->onClick();
                    }
                    if (testButton2->getSprite()->getGlobalBounds().contains(evnt.mouseButton.x, evnt.mouseButton.y)) {
                        testButton2->onClick();
                    }
                    if(evnt.mouseButton.y < 510) {
                        int col_id = (int)(evnt.mouseButton.x / (double)per_col);
                        int row_id = (int)(evnt.mouseButton.y / (double)per_row);
                        if(row_id == 16) {
                            row_id = 15;
                        }
                        if(tiles[row_id][col_id].getState() == Tile::HIDDEN) {
                            if(board[row_id][col_id] == 1) {
                                tiles[row_id][col_id].setState(Tile::EXPLODED);
                            } else {
                                tiles[row_id][col_id].setState(Tile::REVEALED);
                                tiles[row_id][col_id].revealNeighbors();
                            }
                            std::cout << tiles[row_id][col_id].getState() << std::endl;
                            std::cout << board[row_id][col_id] << std::endl;
                        }
                    }
                }
                if(evnt.mouseButton.button == sf::Mouse::Right) {
                    if(evnt.mouseButton.y < 510) {
                        int col_id = (int)(evnt.mouseButton.x / (double)per_col);
                        int row_id = (int)(evnt.mouseButton.y / (double)per_row);
                        if(row_id == 16) {
                            row_id = 15;
                        }
                        std::cout << col_id << " " << row_id << std::endl;
                        std::cout << tiles[row_id][col_id].getState() << std::endl;
                        if(tiles[row_id][col_id].getState() == Tile::HIDDEN) {
                            tiles[row_id][col_id].setState(Tile::FLAGGED);
                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                window.draw(tiles[i][j].sprite);
            }
        }
        window.draw(*newGameButton->getSprite());
        window.draw(*debugButton->getSprite());
        window.draw(*testButton1->getSprite());
        window.draw(*testButton2->getSprite());
        window.display();
    }
}
