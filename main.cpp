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
        sprite.setPosition(x, y);
    }

    sf::Vector2f getPosition() {
        return sprite.getPosition();
    }

    sf::Vector2f getSize() {
        const sf::Vector2u size = texture.getSize();
        const sf::Vector2f scale = sprite.getScale();
        return sf::Vector2f(size.x * scale.x, size.y * scale.y);
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
        sf::Vector2f
        distance(SpaceShip::speedN * delta,
                 0.f);
        if (canMove(distance)) {
            sprite.move(distance);
        }
    }

    void moveLeft(float delta) {
        sf::Vector2f distance(-SpaceShip::speedN * delta, 0.f);
        if (canMove(distance)) {
            sprite.move(distance);
        }
    }

    SpaceShip(sf::RenderWindow *win, std::string imgFile) : Sprite(win, imgFile) {}

private:
    bool canMove(sf::Vector2f distance) {
        float posX = sprite.getPosition().x + distance.x;
        float posY = sprite.getPosition().y + distance.y;
        sf::Vector2u wSize = window->getSize();

        if (posX + getSize().x > wSize.x || posX < 0) {
            return false;
        }
        if (posY + getSize().y > wSize.y || posY < 0) {
            return false;
        }
        return true;
    }

    float speedN = 300;
};

class Fire : public Sprite {
public:
    Fire(sf::RenderWindow *win, std::string imgFile) : Sprite(win, imgFile) {}

    void moveUp(float delta) {
        sf::Vector2f distance(0.f, Fire::speedN * delta);
        sprite.move(distance);
    }

private:
    float speedN = -300;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    std::string shipImage = "assets/ship.png";
    std::string fireImage = "assets/fire.png";

    SpaceShip spaceShip(&window, shipImage);
    spaceShip.setPosition(
            (window.getSize().x - spaceShip.getSize().x) / 2,
            window.getSize().y - spaceShip.getSize().y - 4);

    std::vector<Fire *> fires;

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

            for (unsigned i = 0; i < fires.size(); i++) {
                fires[i]->moveUp(delta);
            }

            lastShot += delta;

            // Check collision

        }

        window.clear();

        if (isPlaying) {
            spaceShip.draw();
            for (unsigned i = 0; i < fires.size(); i++) {
                fires[i]->draw();
            }

        } else {
        }


        window.display();
    }

    return 0;
}