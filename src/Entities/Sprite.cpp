//
// Created by bruno.rezende on 02/10/18.
//

#include "Sprite.h"

Sprite::Sprite(sf::RenderWindow *win, string imgFile) {
    window = win;
    texture.loadFromFile(imgFile);
    sprite.setTexture(texture);
    sprite.setScale(2.5, 2.5);

}

void Sprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Sprite::getPosition() {
    return sprite.getPosition();
}

sf::Vector2f Sprite::getSize() {
    const sf::Vector2u size = texture.getSize();
    const sf::Vector2f scale = sprite.getScale();
    return sf::Vector2f(size.x * scale.x, size.y * scale.y);
}

void Sprite::draw() {
    window->draw(sprite);
}
