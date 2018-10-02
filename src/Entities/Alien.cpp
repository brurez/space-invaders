//
// Created by bruno.rezende on 02/10/18.
//

#include <cmath>
#include "Alien.h"

Alien::Alien(sf::RenderWindow *win, string imgFile) : Sprite(win, imgFile) {
    speed = sf::Vector2f(speedN, 10);
}

void Alien::addSecondTexture(string imgFile) {
    texture2.loadFromFile(imgFile);
}

void Alien::move(float delta) {
    sf::Vector2f distance(speed.x * delta, speed.y * delta);
    sprite.move(distance);
    float d = 1.5f * delta;
    speed = sf::Vector2f(speed.x * cos(d) - speed.y * sin(d), speed.x * sin(d) + speed.y * cos(d));
}

void Alien::setFireTexture() {
    sprite.setTexture(texture2);
}

void Alien::removeFireTexture() {
    sprite.setTexture(texture);
}

vector<Alien *> Alien::build(unsigned n, sf::RenderWindow *win) {
    vector<Alien *> aliens;
    string alienImage1 = "assets/alien-idle.png";

    for (unsigned i = 0; i <= n; i++) {
        aliens.emplace_back(new Alien(win, alienImage1));
        aliens.back()->setPosition(((win->getSize().x - 140) / n) * i + 50, 200);
        aliens.back()->addSecondTexture("assets/alien-firing.png");
    }
    return aliens;
}

