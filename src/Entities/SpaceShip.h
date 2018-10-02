//
// Created by bruno.rezende on 02/10/18.
//

#ifndef SFML_HELLO_SPACESHIP_H
#define SFML_HELLO_SPACESHIP_H


#include "Sprite.h"

class SpaceShip : public Sprite {
public:
    void moveRight(float delta);

    void moveLeft(float delta);

    SpaceShip(sf::RenderWindow *win, string imgFile);

private:
    bool canMove(sf::Vector2f distance);
    float speedN = 300;
};


#endif //SFML_HELLO_SPACESHIP_H
