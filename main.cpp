#include <SFML/Graphics.hpp>
#include <string>

class Position {
public:
    double x;
    double y;
};

class SpaceShip {
public:
    void init(Position position);

    void moveRight(float delta);

    void moveLeft(float delta);

    Position getPosition(void);

    SpaceShip(sf::RenderWindow *win, std::string imgFile);

    void draw(void);

private:
    sf::RenderWindow *window;
    sf::Sprite sprite;
    sf::Texture texture;
    const float speed = 100;
};

SpaceShip::SpaceShip(sf::RenderWindow *win, std::string imgFile) {
    window = win;
    texture.loadFromFile(imgFile);
    sprite.setTexture(texture);
    sprite.setScale(2.5, 2.5);
}

void SpaceShip::draw() {
    window->draw(sprite);
}

void SpaceShip::moveRight(float delta) {
    sprite.move(SpaceShip::speed * delta, 0.f);
}

void SpaceShip::moveLeft(float delta) {
    sprite.move(-SpaceShip::speed * delta, 0.f);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    std::string shipImage = "assets/ship.png";
    SpaceShip spaceShip(&window, shipImage);

    sf::Clock clock;

    const float SHIP_SPEED = 1;
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
            float deltaTime = clock.restart().asSeconds();

            // Move ship
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                spaceShip.moveRight(deltaTime);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                spaceShip.moveLeft(deltaTime);
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