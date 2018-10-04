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
protected:
    vector<sf::Vector2f> buildBox();

    sf::RenderWindow *window;
    sf::Texture texture;
    sf::Vector2f speed;
    sf::Sprite sprite;

public:
    Sprite(sf::RenderWindow *win, string &imgFile);

    void setPosition(float x, float y);

    void setTexture(string imgFile);

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    vector<sf::Vector2f> getBox();

    void draw();
};


#endif //SFML_HELLO_SPRITE_H
