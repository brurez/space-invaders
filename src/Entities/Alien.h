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
    sf::Texture texture2;

public:
    Alien(sf::RenderWindow *win, string imgFile);

    void addSecondTexture(string imgFile);

    void move(float delta);

    void setFireTexture();

    void removeFireTexture();

    static vector<Alien *> build(unsigned n, sf::RenderWindow *win);
};


#endif //SFML_HELLO_ALIEN_H
