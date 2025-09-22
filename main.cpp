#include <SFML/Graphics.hpp>
#include "main.h"

const sf::Keyboard::Key controls[4] = {
    sf::Keyboard::W,   // Player1 Up
    sf::Keyboard::S,   // Player1 Down
    sf::Keyboard::Up,  // Player2 Up
    sf::Keyboard::Down // Player2 Down
};

// Parameters
const sf::Vector2f paddle_size(25.f, 100.f);
const float ball_radius = 10.f;
const int game_width = 800;
const int game_height = 600;
const float paddle_speed = 400.f;
const float paddle_offset_wall = 10.f;
const float time_step = 0.017f; // 60 fps

// Objects of the game
sf::CircleShape ball;
sf::RectangleShape paddles[2];

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode({game_width, game_height}), "PONG");

    // Initialise and load
    init();

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
    // Set size and origin of paddles
    for (sf::RectangleShape& paddle : paddles) {
        paddle.setSize(paddle_size);
        paddle.setOrigin(paddle_size / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ball_radius);
    ball.setOrigin(ball_radius / 2.f, ball_radius / 2.f);
    // Reset paddle position
    paddles[0].setPosition(paddle_offset_wall + paddle_size.x / 2.f, game_height / 2.f);
    paddles[1].setPosition(game_width - paddle_offset_wall - paddle_size.x / 2.f, game_height / 2.f);
    // Reset ball Position
    ball.setPosition(game_width / 2.f, game_height / 2.f);
}

void update(float dt) {
    // Handle paddle movement
    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[0])) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[1])) {
        direction++;
    }
    paddles[0].move(sf::Vector2f(0.f, direction * paddle_speed * dt));
}

void render(sf::RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
}

void clean() {
    // Free up the memory if necessary.
}


