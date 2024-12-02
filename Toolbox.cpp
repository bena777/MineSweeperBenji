
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
void Toolbox::new_button() {
    debug = false;
    newGameButton->setSprite(&new_game_sprite);
    current = true;
    sf::Vector2i dim = sf::Vector2i(25,16);
    gameState = new GameState(sf::Vector2i(dim.x,dim.y));
    board = gameState->board;
    for(int i=0; i<tiles.size(); i++) {
        for(int j=0; j<tiles[0].size();j++) {
            tiles[i][j].setState(Tile::HIDDEN);
        }
    }
    flags = 0;
    displayCounter(window,gameState->getMineCount()-flags,digitsTexture,0,510);
    bombom(dim.y,dim.x);
}
void Toolbox::debug_button() {
    if(not debug) {
        for(int i=0; i<tiles.size(); i++) {
            for(int j=0; j<tiles[0].size();j++) {
                if(board[i][j] ==0) {
                    tiles[i][j].setState(Tile::REVEALED);
                } else {
                    tiles[i][j].setState(Tile::EXPLODED);
                }
            }
        }
    }
    debug = true;
}
void Toolbox::test_1_button() {
    flags = 0;
    newGameButton->setSprite(&new_game_sprite);
    current = true;
    delete gameState;
    gameState = new GameState("P4-data/boards/testboard1.brd");
    board = gameState->board;
    for(int i=0; i<tiles.size(); i++) {
        for(int j=0; j<tiles[0].size();j++) {
            tiles[i][j].setState(Tile::HIDDEN);
        }
    }
}
void Toolbox::test_2_button() {
    flags = 0;
    newGameButton->setSprite(&new_game_sprite);
    current = true;
    delete gameState;
    gameState = new GameState("P4-data/boards/testboard2.brd");
    board = gameState->board;
    tiles.clear();
    int col = board[0].size();
    int row = board.size();
    for(int i=0; i<row*32; i+=32) {
        std::vector<Tile> cur;
        for(int j=0; j<col*32; j+=32) {
            sf::Vector2f tilePosition(j, i); //32 is length/height of tiles
            cur.emplace_back(tilePosition);
        }
        tiles.emplace_back(cur);
    }
    window.clear(sf::Color::White);
    for(int i=0; i<tiles.size(); i++) {
        for(int j=0; j<tiles[0].size();j++) {
            tiles[i][j].setState(Tile::HIDDEN);
            window.draw(tiles[i][j].sprite);
        }
    }
}



 void Toolbox::bombom(int row, int col) { //helper function that sets neighbors and draws tiles
        window.clear(sf::Color::White);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                std::array<Tile *, 8> neighbors = {nullptr,nullptr,nullptr,nullptr,
                    nullptr,nullptr,nullptr,nullptr};
                int bombCount = 0;
                if (i > 0 && j > 0) {
                    neighbors[0] = &tiles[i - 1][j - 1];
                    if (board[i - 1][j - 1] == 1) bombCount++;
                }
                if (i > 0) {
                    neighbors[1] = &tiles[i - 1][j];
                    if (board[i - 1][j] == 1) bombCount++;
                }
                if (i > 0 && j < col - 1) {
                    neighbors[2] = &tiles[i - 1][j + 1];
                    if (board[i - 1][j + 1] == 1) bombCount++;
                }
                if (j < col - 1) {
                    neighbors[3] = &tiles[i][j + 1];
                    if (board[i][j + 1] == 1) bombCount++;
                }
                if (i < row - 1 && j < col - 1) {
                    neighbors[4] = &tiles[i + 1][j + 1];
                    if (board[i + 1][j + 1] == 1) bombCount++;
                }
                if (i < row - 1) {
                    neighbors[5] = &tiles[i + 1][j];
                    if (board[i + 1][j] == 1) bombCount++;
                }
                if (i < row - 1 && j > 0) {
                    neighbors[6] = &tiles[i + 1][j - 1];
                    if (board[i + 1][j - 1] == 1) bombCount++;
                }
                if (j > 0) {
                    neighbors[7] = &tiles[i][j - 1];
                    if (board[i][j - 1] == 1) bombCount++;
                }
                if(tiles[i][j].getState() == Tile::FLAGGED) { //double drawing for flagged
                    tiles[i][j].setState(Tile::HIDDEN);
                    window.draw(tiles[i][j].sprite);
                    tiles[i][j].setState(Tile::FLAGGED);
                }
                if(tiles[i][j].getState() == Tile::EXPLODED) { //double drawing for bombs
                    tiles[i][j].setState(Tile::HIDDEN);
                    window.draw(tiles[i][j].sprite);
                    tiles[i][j].setState(Tile::EXPLODED);
                }
                window.draw(tiles[i][j].sprite);
                if(tiles[i][j].getState() == Tile::REVEALED && (bombCount>0)) {
                    sf::Texture numTexture;
                    std::string yo = "P4-data/images/number_";
                    yo.append(std::to_string(bombCount));
                    yo.append(".png");
                    numTexture.loadFromFile(yo);
                    sf::Sprite numsprite(numTexture);
                    numsprite.setPosition(j*32,i*32);
                    window.draw(numsprite);
                }
                if(tiles[i][j].getState() == Tile::REVEALED && (bombCount ==0)) {
                    for(Tile* tile: neighbors) {
                        tile->revealNeighbors();
                    }
                    tiles[i][j].revealNeighbors();
                }
                tiles[i][j].setNeighbors(neighbors);
            }
        }
}
sf::Sprite getDigitSprite(int digit, const sf::Texture& texture) {
    sf::Sprite sprite(texture);
    int charIndex = (digit == -1) ? 10 : digit;
    sprite.setTextureRect(sf::IntRect(charIndex * 21, 0, 21, 32));
    return sprite;
}
void Toolbox::displayCounter(sf::RenderWindow& window, int number, const sf::Texture& texture, float startX, float startY) {
    std::string numStr = std::to_string(number);
    float x = startX;
    if (number < 0) {
        sf::Sprite minusSprite = getDigitSprite(-1, texture);
        minusSprite.setPosition(x, startY);
        window.draw(minusSprite);
        x += 21;
        numStr = numStr.substr(1);
    }
    if(abs(number) <100) {
        sf::Sprite digitSprite = getDigitSprite(0, texture);
        digitSprite.setPosition(x, startY);
        window.draw(digitSprite);
        x += 21;
    }
    if(abs(number) <10) {
        sf::Sprite digitSprite = getDigitSprite(0, texture);
        digitSprite.setPosition(x, startY);
        window.draw(digitSprite);
        x += 21;
    }
    for (char c : numStr) {
        int digit = c - '0';
        sf::Sprite digitSprite = getDigitSprite(digit, texture);
        digitSprite.setPosition(x, startY);
        window.draw(digitSprite);
        x += 21;
    }
}
Toolbox::Toolbox(){
    gameState = new GameState();
    current = true;
    board = gameState->board;
    int col = board[0].size();
    int row = board.size();
    int per_col = (col*32)/col; //unnecessary lines but whatever
    int per_row = (row*32)/row;
    for(int i=0; i<row*32; i+=32) {
        std::vector<Tile> cur;
        for(int j=0; j<col*32; j+=32) {
            sf::Vector2f tilePosition(j, i); //32 is length/height of tiles
            cur.emplace_back(tilePosition);
        }
        tiles.emplace_back(cur);
    }
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            if(board[i][j] == 0) {
                tiles[i][j].bomb = 0;
            } else {
                tiles[i][j].bomb = 1;
            }
        }
    }
    window.create(sf::VideoMode(800,600), "P4- Minesweeper, Ben Adelman");
    newGameButton = new Button(sf::Vector2f(400, 510),[this]() { new_button(); }
    );
    debugButton = new Button(sf::Vector2f(528, 510), [this]() { debug_button(); }); //impliment functions later
    testButton1 = new Button(sf::Vector2f(592, 510), [this]() { test_1_button(); });
    testButton2 = new Button(sf::Vector2f(656, 510), [this]() { test_2_button(); });

    sf::Texture new_game_bad;
    sf::Texture new_game_good;
    new_game.loadFromFile("P4-data/images/face_happy.png");
    new_game_bad.loadFromFile("P4-data/images/face_lose.png");
    new_game_good.loadFromFile("P4-data/images/face_win.png");
    new_game_sprite.setTexture(new_game);
    sf::Sprite new_game_bad_sprite(new_game_bad);
    sf::Sprite new_game_good_sprite(new_game_good);
    newGameButton->setSprite(&new_game_sprite);

    sf::Texture debug;
    debug.loadFromFile("P4-data/images/debug.png");
    sf::Sprite debug_sprite(debug);
    debugButton->setSprite(&debug_sprite);

    sf::Texture test_1;
    test_1.loadFromFile("P4-data/images/test_1.png");
    sf::Sprite test1_sprite(test_1);
    testButton1->setSprite(&test1_sprite);

    sf::Texture test_2;
    test_2.loadFromFile("P4-data/images/test_2.png");
    sf::Sprite test2_sprite(test_2);
    testButton2->setSprite(&test2_sprite);

    sf::Texture digitsTexture;
    digitsTexture.loadFromFile("P4-data/images/digits.png");

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
                    if(evnt.mouseButton.y < row*per_row) {
                        int col_id = (int)(evnt.mouseButton.x / (double)per_col);
                        int row_id = (int)(evnt.mouseButton.y / (double)per_row);
                        if(row_id == row) {
                            row_id = row-1;
                        }
                        if(tiles[row_id][col_id].getState() == Tile::HIDDEN && current) {
                            if(board[row_id][col_id] == 1) {
                                current = false;
                                newGameButton->setSprite(&new_game_bad_sprite);
                                tiles[row_id][col_id].setState(Tile::EXPLODED);
                                for(int i=0; i<row; i++) {
                                    for(int j=0; j<col; j++) {
                                        if(board[i][j] == 1) {
                                            tiles[i][j].setState(Tile::EXPLODED);
                                        }
                                    }
                                }
                            } else {
                                tiles[row_id][col_id].setState(Tile::REVEALED);
                                tiles[row_id][col_id].revealNeighbors();
                            }
                        }
                    }
                }
                if(evnt.mouseButton.button == sf::Mouse::Right) {
                    if(evnt.mouseButton.y < 510) {
                        int col_id = (int)(evnt.mouseButton.x / (double)per_col);
                        int row_id = (int)(evnt.mouseButton.y / (double)per_row);
                        if(row_id == row) {
                            row_id = row-1;
                        }
                        tiles[row_id][col_id].onClickRight();
                        if(tiles[row_id][col_id].getState() == Tile::FLAGGED) {
                            flags++;
                        }
                        if(tiles[row_id][col_id].getState() == Tile::HIDDEN) {
                            flags--;
                        }
                        std::string numStr = std::to_string(gameState->getMineCount()-flags);
                        int num = gameState->getMineCount()-flags;
                        int x = 20;
                        if (num<0) {
                            sf::Sprite minusSprite = getDigitSprite(-1, digitsTexture);
                            minusSprite.setPosition(x, 510);
                            window.draw(minusSprite);
                            x += 21;
                            numStr = numStr.substr(1);
                        }
                        for (char c : numStr) {
                            int digit = c - '0';
                            sf::Sprite digitSprite = getDigitSprite(digit, digitsTexture);
                            digitSprite.setPosition(x, 510);
                            window.draw(digitSprite);
                            x += 21;
                        }
                    }
                }
            }
            bombom(row,col);
            displayCounter(window,gameState->getMineCount()-flags,digitsTexture,0,510);
            window.draw(*newGameButton->getSprite());
            window.draw(*debugButton->getSprite());
            window.draw(*testButton1->getSprite());
            window.draw(*testButton2->getSprite());
            window.display();
        }
    }
}
