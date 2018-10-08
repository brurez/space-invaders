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

    float lastPlayerFire = 1;
    float lastAlienFire = 0;
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
                    lastPlayerFire = 1;
                    aliens = Game::buildAliens(&window, alien1);
                    clock.restart();
                }
            }
        }

        if (isPlaying) {
            float delta = clock.restart().asSeconds();

            // MOVEMENT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                spaceShip.moveRight(delta);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                spaceShip.moveLeft(delta);
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

            // CHECK COLLISIONS

            for (unsigned i = 0; i < aliens.size(); i++) {
                for (unsigned j = 0; j < pFires.size(); j++) {
                    if (Collision::BoundingBoxTest(aliens[i], pFires[j])) {
                        aliens.erase(aliens.begin() + i);
                        pFires.erase(pFires.begin() + j);
                    }
                }
                aliens[i]->setTexture(alien2);
            }

            for (unsigned j = 0; j < aFires.size(); j++) {
                if (Collision::BoundingBoxTest(aFires[j], &spaceShip)) {
                    aFires.erase(aFires.begin() + j);
                    isPlaying = false;
                }

            }

            // PLAYER FIRE

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (lastPlayerFire >= 0.5) {
                    pFires.emplace_back(new Fire(&window, fireImage));
                    pFires.back()->setPosition(
                            spaceShip.getPosition().x + spaceShip.getSize().x / 2 - 6,
                            spaceShip.getPosition().y - spaceShip.getSize().y);
                    lastPlayerFire = 0;
                }
            }

            // ALIEN FIRE

            if(lastAlienFire > 0.5) {
                unsigned int r = rand() % aliens.size();

                aFires.emplace_back(new Fire(&window, fireImage));
                aFires.back()->setPosition(
                        aliens[r]->getPosition().x + aliens[r]->getSize().x / 2 - 6,
                        aliens[r]->getPosition().y + aliens[r]->getSize().y);
                aFires.back()->setRotation(180);
                aFires.back()->setColor(sf::Color(100, 255, 100));

                lastAlienFire = 0;
            }

            // WIN CONDITION

            if (aliens.size() == 0) {
                isPlaying = false;
                win = true;
            }

            lastPlayerFire += delta;
            lastAlienFire += delta;
        }

        window.clear();

        // DRAW

        if (isPlaying) {
            bg.draw();
            spaceShip.draw();

            for (auto &fire : pFires) {
                fire->draw();
            }

            for (auto &fire : aFires) {
                fire->draw();
            }

            for (auto &alien : aliens) {
                alien->draw();
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