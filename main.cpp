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
        sf::Vector2f distance(SpaceShip::speed * delta, 0.f);
        if(canMove(distance)){
            sprite.move(distance);
        }
    }

    void moveLeft(float delta) {
        sf::Vector2f distance(-SpaceShip::speed * delta, 0.f);
        if(canMove(distance)){
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

    float speed = 300;
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