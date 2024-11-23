
#ifndef PROJECT4_BUTTON_H
#define PROJECT4_BUTTON_H
#include <SFML/Graphics.hpp>


class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
};


#endif //PROJECT4_BUTTON_H
