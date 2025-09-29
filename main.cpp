#include <iostream>
#include <SFML/Graphics.hpp>
#include "main.h"

// Parameters
const int game_width = 800;
const int game_height = 600;
const float time_step = 0.017f; // 60 fps

sf::Texture spritesheet;
sf::Sprite invader;

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode({game_width, game_height}), "Space Invaders");

    // Initialise and load
    init();
    reset();

    while (window.isOpen()) {
        //Calculate dt
        static sf::Clock clock;
        const float dt = clock.restart().asSeconds();

        window.clear();
        update(dt);
        render(window);
        // Wait for the time_step to finish before displaying the next frame
        sf::sleep(sf::seconds(time_step));
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
    clean();
    return 0;
}

void init() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32)));
}

void reset() {
}

void update(float dt) {
}

void render(sf::RenderWindow& window) {
    // Draw Everything
    window.draw(invader);
}

void clean() {
    // Free up the memory if necessary.
}


