#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 640), "Space Invaders", sf::Style::Close);
    window.setVerticalSyncEnabled(true);

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
            if( (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                if( !isPlaying ) {
                    // restart game
                    isPlaying = true;
                    clock.restart();
                }
            }
        }

        window.clear();

        if (isPlaying) {
            // draw world

        } else {
            //is paused
        }


        window.display();
    }

    return 0;
}