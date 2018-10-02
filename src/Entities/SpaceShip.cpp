//
// Created by bruno.rezende on 02/10/18.
//

#include "SpaceShip.h"

SpaceShip::SpaceShip(sf::RenderWindow *win, string imgFile) : Sprite(win, imgFile) {}

void SpaceShip::moveRight(float delta) {
    sf::Vector2f
            distance(SpaceShip::speedN * delta,
                     0.f);
    if (canMove(distance)) {
        sprite.move(distance);
    }
}

void SpaceShip::moveLeft(float delta) {
    sf::Vector2f distance(-SpaceShip::speedN * delta, 0.f);
    if (canMove(distance)) {
        sprite.move(distance);
    }
}

bool SpaceShip::canMove(sf::Vector2f distance) {
    float posX = sprite.getPosition().x + distance.x;
    float posY = sprite.getPosition().y + distance.y;
    sf::Vector2u wSize = window->getSize();

    if (posX + getSize().x > wSize.x || posX < 0) {
        return false;
    }
    if (posY + getSize().y > wSize.y || posY < 0) {
        return false;
    }
    return true;
}

float speedN = 300;
