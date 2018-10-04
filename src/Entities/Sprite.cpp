//
// Created by bruno.rezende on 02/10/18.
//

#include "Sprite.h"

Sprite::Sprite(sf::RenderWindow *win, string &imgFile) {
    window = win;
    setTexture(imgFile);
    sprite.setScale(2.5, 2.5);
}

void Sprite::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Sprite::setTexture(string imgFile) {
    texture.loadFromFile(imgFile);
    sprite.setTexture(texture);
}

sf::Vector2f Sprite::getPosition() {
    return sprite.getPosition();
}

sf::Vector2f Sprite::getSize() {
    const sf::Vector2u size = texture.getSize();
    const sf::Vector2f scale = sprite.getScale();
    return sf::Vector2f(size.x * scale.x, size.y * scale.y);
}

vector<sf::Vector2f> Sprite::getBox()  {
    return buildBox();
}

void Sprite::setRepeated(bool value) {
    texture.setRepeated(true);
    sprite.setTexture(texture);
}

void Sprite::setTextureRect(const sf::IntRect& rect) {
    sprite.setTextureRect(rect);
}

void Sprite::draw() {
    window->draw(sprite);
}

vector<sf::Vector2f> Sprite::buildBox() {
    sf::Transform trans = sprite.getTransform();
    sf::IntRect local = sprite.getTextureRect();

    vector<sf::Vector2f> box = {
            trans.transformPoint(0.f, 0.f),
            trans.transformPoint(local.width, 0.f),
            trans.transformPoint(local.width, local.height),
            trans.transformPoint(0.f, local.height)
    };
    return box;
}
