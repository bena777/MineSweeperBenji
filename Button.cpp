
#include <iostream>
#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void()> _onClick) {
    button_shape.setSize(sf::Vector2f(100,50));
    position = _position;
    button_shape.setPosition(_position);
    onClickCallback = _onClick;
    sprite = nullptr;
}

sf::Vector2f Button::getPosition() {
    return position;
}
sf::Sprite *Button::getSprite() {
    return sprite;
}
void Button::setSprite(sf::Sprite *_sprite) {
    sprite = _sprite;
    sprite->setPosition(position);
}
void Button::onClick() {
    if(onClickCallback) {
        onClickCallback();
    }
}


