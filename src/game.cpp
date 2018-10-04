//
// Created by bruno.rezende on 02/10/18.
//

#include "Entities/Alien.h"

namespace Game {
    vector<Alien *> buildAliens(sf::RenderWindow *win, string &imgFile) {
        vector<Alien *> aliens;
        unsigned int n = 7;

        for (unsigned i = 0; i <= n - 1; i++) {
            aliens.emplace_back(new Alien(win, imgFile));
            aliens.back()->setPosition(((win->getSize().x - 100) / n) * i + 75, 125);
        }

        for (unsigned i = 0; i <= n; i++) {
            aliens.emplace_back(new Alien(win, imgFile));
            aliens.back()->setPosition(((win->getSize().x - 140) / n) * i + 50, 200);
        }

        for (unsigned i = 0; i <= n - 1
        ; i++) {
            aliens.emplace_back(new Alien(win, imgFile));
            aliens.back()->setPosition(((win->getSize().x - 100) / n) * i + 75, 275);
        }
        return aliens;
    }
}

