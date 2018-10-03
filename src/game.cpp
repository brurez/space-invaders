//
// Created by bruno.rezende on 02/10/18.
//

#include "Entities/Alien.h"

namespace Game {
    vector<Alien *> buildAliens(unsigned n, sf::RenderWindow *win, string &imgFile) {
        vector<Alien *> aliens;

        for (unsigned i = 0; i <= n; i++) {
            aliens.emplace_back(new Alien(win, imgFile));
            aliens.back()->setPosition(((win->getSize().x - 140) / n) * i + 50, 200);
        }
        return aliens;
    }
}

