#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "Collision.h"
#include "Entities/Sprite.h"
#include "Entities/SpaceShip.h"
#include "Entities/Fire.h"
#include "Entities/Alien.h"
#include "game.h"

using namespace std;

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 640;

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    string shipImage = "assets/ship.png";
    string fireImage = "assets/fire.png";

    string alien1 = "assets/alien-idle.png";
    string alien2 = "assets/alien-firing.png";

    string spaceBg = "assets/space.png";

    SpaceShip spaceShip(&window, shipImage);
    spaceShip.setPosition(
            (window.getSize().x - spaceShip.getSize().x) / 2,
            window.getSize().y - spaceShip.getSize().y - 4);

    Sprite bg(&window, spaceBg);
    bg.setTextureRect({0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    bg.setRepeated(true);

    std::vector<Fire *> pFires;
    std::vector<Fire *> aFires;
    std::vector<Alien *> aliens;

    sf::Clock clock;

    float lastShot = 1;
    bool isPlaying = false;
    bool win = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Window closed or escape key pressed: exit
            if ((event.type == sf::Event::Closed) ||
                ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                window.close();
                break;
            }

            // Space key pressed: play
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Return)) {
                if (!isPlaying) {
                    // restart game
                    isPlaying = true;
                    win = false;
                    lastShot = 1;
                    aliens = Game::buildAliens(&window, alien1);
                    clock.restart();
                }
            }
        }

        if (isPlaying) {
            float delta = clock.restart().asSeconds();

            // Move ship
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                spaceShip.moveRight(delta);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                spaceShip.moveLeft(delta);
            }

            // Fires a new shot
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (lastShot >= 0.5) {
                    pFires.emplace_back(new Fire(&window, fireImage));
                    pFires.back()->setPosition(
                            spaceShip.getPosition().x + spaceShip.getSize().x / 2 - 6,
                            spaceShip.getPosition().y - spaceShip.getSize().y);
                    lastShot = 0;
                }
            }

            for (auto &fire : pFires) {
                fire->moveUp(delta);
            }

            for (auto &fire : aFires) {
                fire->moveDown(delta);
            }

            for (auto &alien : aliens) {
                alien->move(delta);
            }

            lastShot += delta;
        }

        window.clear();

        if (isPlaying) {
            bg.draw();
            spaceShip.draw();

            for (auto &fire : pFires) {
                fire->draw();
            }

            for (auto &fire : aFires) {
                fire->draw();
            }

            for (unsigned i = 0; i < aliens.size(); i++) {
                for (unsigned j = 0; j < pFires.size(); j++) {
                    if (Collision::BoundingBoxTest(aliens[i], pFires[j])) {
                        aliens.erase(aliens.begin() + i);
                        pFires.erase(pFires.begin() + j);
                    }
                }
                aliens[i]->draw();

                int r = rand() % 500;
                if (r == 1) {
                    aliens[i]->setTexture(alien2);

                    aFires.emplace_back(new Fire(&window, fireImage));
                    aFires.back()->setPosition(
                            aliens[i]->getPosition().x + aliens[i]->getSize().x / 2 - 6,
                            aliens[i]->getPosition().y + aliens[i]->getSize().y);
                    aFires.back()->setRotation(180);
                    aFires.back()->setColor(sf::Color(100, 255, 100));

                } else if (r == 2) {
                    aliens[i]->setTexture(alien1);
                }
            }

            for (unsigned j = 0; j < aFires.size(); j++) {
                if (Collision::BoundingBoxTest(aFires[j], &spaceShip)) {
                    aFires.erase(aFires.begin() + j);
                    isPlaying = false;
                }

            }

            if (aliens.size() == 0) {
                isPlaying = false;
                win = true;
            }

        } else {
            string img;
            if (win) {
                img = "assets/win.png";
            } else {
                img = "assets/intro.png";
            }

            Sprite title = Sprite(&window, img);
            title.setPosition((SCREEN_WIDTH - title.getSize().x) / 2, (SCREEN_HEIGHT - title.getSize().y) / 2);
            title.draw();
            aliens.clear();
            aFires.clear();
            pFires.clear();
        }

        window.display();
    }

    return 0;
}