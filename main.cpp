#include <SFML/Graphics.hpp>
#include "main.h"

sf::Vector2f ball_velocity;
bool is_player_serving = true;
const float initial_velocity_x = 100.f;  // Horizontal velocity
const float initial_velocity_y = 60.f;  // Vertical velocity
const float velocity_multiplier = 1.1f;  // How much the ball will speed up everytime it hits a paddle. Here, 10% every time

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

sf::Font font;
sf::Text text;

int player1_score = 0;
int player2_score = 0;

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode({game_width, game_height}), "PONG");

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
    // Set size and origin of paddles
    for (sf::RectangleShape& paddle : paddles) {
        paddle.setSize(paddle_size);
        paddle.setOrigin(paddle_size / 2.f);
    }
    // Set size and origin of ball
    ball.setRadius(ball_radius);
    ball.setOrigin(ball_radius / 2.f, ball_radius / 2.f);


    // Load font-face from res dir
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
    // Set text element to use font
    text.setFont(font);
    // Set the character size to 24 pixels
    text.setCharacterSize(24);
}

void reset() {
    ball_velocity = {(is_player_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y};

    // Reset paddle position
    paddles[0].setPosition(paddle_offset_wall + paddle_size.x / 2.f, game_height / 2.f);
    paddles[1].setPosition(game_width - paddle_offset_wall - paddle_size.x / 2.f, game_height / 2.f);
    // Reset ball Position
    ball.setPosition(game_width / 2.f, game_height / 2.f);

    // Update Score Text
    text.setString(std::to_string(player1_score) + " : " + std::to_string(player2_score));
    // Keep Score Text Centered
    text.setPosition((game_width * .5f) - (text.getLocalBounds().width * .5f), 0);
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
    
    direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(controls[2])) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(controls[3])) {
        direction++;
    }
    paddles[1].move(sf::Vector2f(0.f, direction * paddle_speed * dt));

    ball.move(ball_velocity * dt);
    // Check ball collision
    const float bx = ball.getPosition().x;
    const float by = ball.getPosition().y;
    if (by > game_height) {  // Bottom wall
        //  Bottom wall
        ball_velocity.x *= velocity_multiplier;
        ball_velocity.y *= -velocity_multiplier;
        ball.move(sf::Vector2f(0.f, -10.f));
    } else if (by < 0) {  // Top wall
        // Top wall
        ball_velocity.x *= velocity_multiplier;
        ball_velocity.y *= -velocity_multiplier;
        ball.move(sf::Vector2f(0.f, 10.f));
    } else if (bx > game_width) {
        // Right wall
        player1_score++;
        is_player_serving = false;
        reset();
    } else if (bx < 0) {
        // Left wall
        player2_score++;
        is_player_serving = true;
        reset();
    } else if (bx < paddle_size.x + paddle_offset_wall && by > paddles[0].getPosition().y - (paddle_size.y * 0.5) && by < paddles[0].getPosition().y + (paddle_size.y * 0.5)) {  // Ball is inline or behind paddle AND Ball is below top edge of paddle AND Ball is above bottom edge of paddle
        // Bounce off left paddle
        ball_velocity.x *= -velocity_multiplier;
        ball_velocity.y *= velocity_multiplier;
        ball.move(sf::Vector2f(10.f, 0.f));
    } else if (bx > game_width - paddle_size.x - paddle_offset_wall && by > paddles[1].getPosition().y - (paddle_size.y * 0.5) && by < paddles[1].getPosition().y + (paddle_size.y * 0.5)) {
        // Bounce off right paddle
        ball_velocity.x *= -velocity_multiplier;
        ball_velocity.y *= velocity_multiplier;
        ball.move(sf::Vector2f(-10.f, 0.f));
    }
}

void render(sf::RenderWindow& window) {
    // Draw Everything
    window.draw(paddles[0]);
    window.draw(paddles[1]);
    window.draw(ball);
    window.draw(text);
}

void clean() {
    // Free up the memory if necessary.
}


