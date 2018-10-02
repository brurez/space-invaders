//
// Created by bruno.rezende on 02/10/18.
//

#ifndef SFML_HELLO_FIRE_H
#define SFML_HELLO_FIRE_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Sprite.h"

class Fire : public Sprite {
public:
    Fire(sf::RenderWindow *win, string imgFile);

    void moveUp(float delta);

private:
    float speedN = -300;
};


#endif //SFML_HELLO_FIRE_H
