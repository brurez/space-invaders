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


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    string shipImage = "assets/ship.png";
    string fireImage = "assets/fire.png";

    string alien1 = "assets/alien-idle.png";
    string alien2 = "assets/alien-firing.png";

    SpaceShip spaceShip(&window, shipImage);
    spaceShip.setPosition(
            (window.getSize().x - spaceShip.getSize().x) / 2,
            window.getSize().y - spaceShip.getSize().y - 4);

    string spaceBg = "assets/space.png";
    Sprite bg(&window, spaceBg);
    bg.setTextureRect({0, 0, 800, 600});
    bg.setRepeated(true);

    std::vector<Fire *> fires;
    std::vector<Alien *> aliens;
    aliens = Game::buildAliens(8, &window, alien1);

    sf::Clock clock;

    float lastShot = 1;
    bool isPlaying = false;

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
                    lastShot = 1;
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
                    fires.emplace_back(new Fire(&window, fireImage));
                    fires.back()->setPosition(
                            spaceShip.getPosition().x + spaceShip.getSize().x / 2 - 6,
                            spaceShip.getPosition().y - spaceShip.getSize().y);
                    lastShot = 0;
                }
            }

            for (auto &fire : fires) {
                fire->moveUp(delta);
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

            for (auto &fire : fires) {
                fire->draw();
            }

            for (unsigned i = 0; i < aliens.size(); i++) {
                for (auto &fire : fires) {
                    if(Collision::BoundingBoxTest(aliens[i], fire)){
                        aliens.erase(aliens.begin() + i);
                    }
                }
                aliens[i]->draw();
                int r = rand() % 20;
                if (r == 5) {
                    aliens[i]->setTexture(alien2);
                } else if (r == 6) {
                    aliens[i]->setTexture(alien1);

                }
            }

        } else {
            string introImg = "assets/intro.png";
            Sprite title = Sprite(&window, introImg);
            title.setPosition(140, 160);
            title.draw();
        }


        window.display();
    }

    return 0;
}