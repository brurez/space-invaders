#include <SFML/Graphics.hpp>
#include <string>

class Position {
public:
    double x;
    double y;
};

class Entity {
public:
    void init(Position position);

    void move(Position position);

    Position getPosition(void);

    Entity(sf::RenderWindow *win, std::string imgFile);

    void draw(void);

private:
    sf::RenderWindow *window;
    sf::Sprite sprite;
    sf::Texture texture;
};

Entity::Entity(sf::RenderWindow *win, std::string imgFile) {
    window = win;
    texture.loadFromFile(imgFile);
    sprite.setTexture(texture);
}

void Entity::draw() {
    window->draw(sprite);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    std::string shipImage = "assets/ship.png";
    Entity spaceShip(&window, shipImage);

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
            float deltaTime = clock.restart().asSeconds();

            // Move ship
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

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