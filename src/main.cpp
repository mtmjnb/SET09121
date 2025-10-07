#include <SFML/Graphics.hpp>
#include "game_parameters.hpp"
#include "game_system.hpp"

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode({Parameters::game_width, Parameters::game_height}), "Space Invaders");

    // Initialise
    GameSystem::init();

    while (window.isOpen()) {
        // Calculate delta time
        static sf::Clock clock;
        const float delta_time = clock.restart().asSeconds();

        window.clear();
        GameSystem::update(delta_time);
        GameSystem::render(window);
        // Wait for the time_step to finish before displaying the next frame
        sf::sleep(sf::seconds(Parameters::time_step));
        // Wait for Vsync
        window.display();
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    // Unload and shutdown
    GameSystem::clean();
    return 0;
}


