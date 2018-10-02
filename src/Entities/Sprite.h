//
// Created by bruno.rezende on 02/10/18.
//

#ifndef SFML_HELLO_SPRITE_H
#define SFML_HELLO_SPRITE_H


#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace std;

class Sprite {
public:
    Sprite(sf::RenderWindow *win, string imgFile);

    void setPosition(float x, float y);

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    void draw();

    sf::Sprite sprite;
protected:
    sf::RenderWindow *window;
    sf::Texture texture;
};


#endif //SFML_HELLO_SPRITE_H
