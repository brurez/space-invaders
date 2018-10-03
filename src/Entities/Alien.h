//
// Created by bruno.rezende on 02/10/18.
//

#ifndef SFML_HELLO_ALIEN_H
#define SFML_HELLO_ALIEN_H


#include <SFML/Graphics/Texture.hpp>
#include "Sprite.h"

class Alien : public Sprite {
    sf::Vector2f speed;
    float speedN = 50;

public:
    Alien(sf::RenderWindow *win, string imgFile);

    void move(float delta);
};


#endif //SFML_HELLO_ALIEN_H
