//
// Created by bruno.rezende on 02/10/18.
//

#ifndef SFML_HELLO_GAME_H
#define SFML_HELLO_GAME_H

#include "Entities/Alien.h"

namespace Game {
    vector<Alien *> buildAliens(sf::RenderWindow *win, string &imgFile);
}

#endif //SFML_HELLO_GAME_H
