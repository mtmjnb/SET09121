#include "components.hpp"
#include "engine/renderer.hpp"
#include "engine/tile_level_loader/level_system.hpp"
#include "game_parameters.hpp"

// ================================================================ ShapeComponent ================================================================

void ShapeComponent::update(const float& delta_time) {
    shape->setPosition(parent->get_position());
}

void ShapeComponent::render() { Renderer::queue(shape.get()); }

sf::Shape& ShapeComponent::get_shape() const { return *shape; }

ShapeComponent::ShapeComponent(Entity* parent) : Component(parent), shape(std::make_shared<sf::CircleShape>()) {}

// ================================================================ ActorMovementComponent ================================================================

void ActorMovementComponent::update(const float& delta_time) {}

ActorMovementComponent::ActorMovementComponent(Entity* parent)
    : speed(100.0f), Component(parent) {}

//bool ActorMovementComponent::valid_move(const sf::Vector2f& position) {
//    return (LevelSystem::get_tile_at(position) != LevelSystem::WALL);
//}

void ActorMovementComponent::move(const sf::Vector2f& position_change) {
    sf::Vector2f new_position = this->parent->get_position() + position_change;
    //if (valid_move(new_position)) {
        this->parent->set_position(new_position);
    //}
}

void ActorMovementComponent::move(float x, float y) {
    move(sf::Vector2f(x, y));
}

float ActorMovementComponent::get_speed() const {
    return ActorMovementComponent::speed;
}

void ActorMovementComponent::set_speed(float speed) {
    ActorMovementComponent::speed = speed;
}

// ================================================================ PlayerMovementComponent ================================================================

PlayerMovementComponent::PlayerMovementComponent(Entity* parent)
    : ActorMovementComponent(parent) {}

void PlayerMovementComponent::update(const float& delta_time) {
    float direction_x = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direction_x--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direction_x++;
    }
    float direction_y = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direction_y--;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direction_y++;
    }

    // x and y should be checked individually incase movement on one axis isn't alowed but the other is
    sf::Vector2f position_change_x = sf::Vector2f(direction_x * Parameters::player_speed * delta_time, 0.0f);
    //if (valid_move(this->get_position() + position_change_x)) {
        this->move(position_change_x);
    //}
    sf::Vector2f position_change_y = sf::Vector2f(0.0f, direction_y * Parameters::player_speed * delta_time);
    //if (valid_move(this->get_position() + position_change_y)) {
        this->move(position_change_y);
    //}
}

// ================================================================ EnemyAIComponent ================================================================

EnemyAIComponent::EnemyAIComponent(Entity* parent)
    : ActorMovementComponent(parent) {}