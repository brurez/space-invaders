//
// Created by bruno.rezende on 02/10/18.
//

#include "Fire.h"

Fire::Fire(sf::RenderWindow *win, string imgFile) : Sprite(win, imgFile) {}

void Fire::moveUp(float delta) {
    sf::Vector2f distance(0.f, -Fire::speedN * delta);
    sprite.move(distance);
}
