
#include "GameState.h"


GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines){
    int mines_placed = 0;
    srand(time(NULL));
    for(int i=0; mines_placed<_numberOfMines; i++){
        int num = (rand() % _dimensions.x) + 1;
        int num2 = (rand() & _dimensions.y) + 1;

        std::cout << num;
    }
}