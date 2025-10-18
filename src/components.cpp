#include "components.hpp"
#include "engine/game_system.hpp"
#include "engine/renderer.hpp"
#include "engine/tile_level_loader/level_system.hpp"
#include "game_parameters.hpp"
#include "scenes.hpp"

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

bool ActorMovementComponent::valid_move(const sf::Vector2f& position) {
    return (LevelSystem::get_tile_at(position) != LevelSystem::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& position_change) {
    sf::Vector2f new_position = this->parent->get_position() + position_change;
    if (valid_move(new_position)) {
        this->parent->set_position(new_position);
    }
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
    sf::Vector2f position_change_x = sf::Vector2f(direction_x * this->speed * delta_time, 0.0f);
    if (valid_move(this->parent->get_position() + position_change_x)) {
        this->move(position_change_x);
    }
    sf::Vector2f position_change_y = sf::Vector2f(0.0f, direction_y * this->speed * delta_time);
    if (valid_move(this->parent->get_position() + position_change_y)) {
        this->move(position_change_y);
    }
}

// ================================================================ EnemyAIComponent ================================================================

EnemyAIComponent::EnemyAIComponent(Entity* parent)
    : ActorMovementComponent(parent) {
    this->state = ROTATING;
}

static const sf::Vector2i directions[] = { {1, 0}, {0, 1}, {0, -1}, {-1, 0} };

void EnemyAIComponent::update(const float& delta_time) {
    const float amount_to_move = static_cast<float>(delta_time * this->speed);
    const sf::Vector2f curent_position = this->parent->get_position();
    const sf::Vector2f next_position = curent_position + this->direction * amount_to_move;
    const sf::Vector2i bad_direction = -1 * sf::Vector2i(this->direction);  // Inverse of our current direction
    sf::Vector2i new_direction = directions[(rand() % 4)];

    switch (this->state) {
        case ROAMING:
            if (!this->valid_move(next_position) || LevelSystem::get_tile_at(curent_position) == LevelSystem::WAYPOINT) {  // Wall in front or at waypoint
                // Start rotate
                this->state = ROTATING;
            } else {
                // Keep moving
                this->move(this->direction * amount_to_move);
            }
            break;

        case ROTATING:
            while (new_direction == bad_direction || LevelSystem::get_tile_at(curent_position + (sf::Vector2f(new_direction) * LevelSystem::get_tile_size())) == LevelSystem::WALL) {  // Don't reverse and don't pick a direction that will lead to a wall
                new_direction = directions[(rand() % 4)];
            }
            this->direction = sf::Vector2f(new_direction);
            this->state = ROTATED;
            break;

        case ROTATED:
            // Have we left the waypoint?
            if (LevelSystem::get_tile_at(curent_position) != LevelSystem::WAYPOINT) {
                this->state = ROAMING;  // Yes
            }
            move(this->direction * amount_to_move);  // No
            break;
    }
    ActorMovementComponent::update(delta_time);
}

// ================================================================ PickupComponent ================================================================

PickupComponent::PickupComponent(Entity* parent, bool big)
    : ShapeComponent(parent) {
    this->big = big;
}

void PickupComponent::update(const float& delta_time) {
    for (std::shared_ptr<Entity> entity : GameSystem::get_active_scene()->get_entities()) {  // Every entity in the scene
        if (vector_distance(entity->get_position(), this->parent->get_position()) < 30.0f) {  // Within 30.f unit of me
            std::vector<std::shared_ptr<PlayerMovementComponent>> component =
                entity->get_compatible_components<PlayerMovementComponent>();  // Get the entity PlayerMovementComponent, if it has one
            if (!component.empty()) {  // If it has one
                // nom nom
                this->parent->set_for_delete();  // Delete myself
                break;  // Stop looking
            }
        }
    }
}