//
// Created by bruno.rezende on 02/10/18.
//

#include <cmath>
#include "Alien.h"

Alien::Alien(sf::RenderWindow *win, string imgFile) : Sprite(win, imgFile) {
    speed = sf::Vector2f(speedN, 10);
}

void Alien::move(float delta) {
    sf::Vector2f distance(speed.x * delta, speed.y * delta);
    sprite.move(distance);
    float d = 1.5f * delta;
    speed = sf::Vector2f(speed.x * cos(d) - speed.y * sin(d), speed.x * sin(d) + speed.y * cos(d));
}

