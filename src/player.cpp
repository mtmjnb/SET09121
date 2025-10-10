#include "tile_level_loader/level_system.hpp"
#include "player.hpp"
#include "game_parameters.hpp"

void Player::update(const float& delta_time) {
    Entity::update(delta_time);

    // Move in four directions based on keys
    float direction_x = 0.0f;
    if (sf::Keyboard::isKeyPressed(Parameters::controls[1]) || sf::Keyboard::isKeyPressed(Parameters::controls[5])) {  // Left
        direction_x--;
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[3]) || sf::Keyboard::isKeyPressed(Parameters::controls[7])) {  // Right
        direction_x++;
    }
    float direction_y = 0.0f;
    if (sf::Keyboard::isKeyPressed(Parameters::controls[0]) || sf::Keyboard::isKeyPressed(Parameters::controls[4])) {  // Up
        direction_y--;
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[2]) || sf::Keyboard::isKeyPressed(Parameters::controls[6])) {  // Down
        direction_y++;
    }

    // x and y should be checked individually incase movement on one axis isn't alowed but the other is
    sf::Vector2f position_change_x = sf::Vector2f(direction_x * Parameters::player_speed * delta_time, 0.0f);
    if (valid_move(this->get_position() + position_change_x)) {
        this->move(position_change_x);
    }
    sf::Vector2f position_change_y = sf::Vector2f(0.0f, direction_y * Parameters::player_speed * delta_time);
    if (valid_move(this->get_position() + position_change_y)) {
        this->move(position_change_y);
    }
}

Player::Player()
    : Entity(std::make_unique<sf::CircleShape>(radius)) {
    shape->setFillColor(sf::Color::Magenta);
    shape->setOrigin(sf::Vector2f(radius, radius));
}

void Player::render(sf::RenderWindow& window) const {
    window.draw(*shape);
}

bool Player::valid_move(sf::Vector2f position) {
    return (LevelSystem::get_tile_at(position) != LevelSystem::WALL);
}