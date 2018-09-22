#include <SFML/Graphics.hpp>
#include <string>

class Sprite {
public:
    Sprite(sf::RenderWindow *win, std::string imgFile) {
        window = win;
        texture.loadFromFile(imgFile);
        sprite.setTexture(texture);
        sprite.setScale(2.5, 2.5);

    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);  //400, 580);
    }

    void draw() {
        window->draw(sprite);
    }

protected:
    sf::RenderWindow *window;
    sf::Sprite sprite;
    sf::Texture texture;
};


class SpaceShip : public Sprite {
public:
    void moveRight(float delta) {
        sprite.move(SpaceShip::speed * delta, 0.f);
    }

    void moveLeft(float delta) {
        sprite.move(-SpaceShip::speed * delta, 0.f);
    }

    SpaceShip(sf::RenderWindow *win, std::string imgFile) : Sprite(win, imgFile) {}

private:
    float speed = 140;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    std::string shipImage = "assets/ship.png";
    SpaceShip spaceShip(&window, shipImage);
    spaceShip.setPosition(400, 580);

    sf::Clock clock;

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
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                if (!isPlaying) {
                    // restart game
                    isPlaying = true;
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

            // Check collision

        }

        window.clear();

        if (isPlaying) {
            spaceShip.draw();

        } else {
        }


        window.display();
    }

    return 0;
}