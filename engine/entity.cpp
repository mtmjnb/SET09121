#include "entity.hpp"
#include "renderer.hpp"

Entity::Entity(std::unique_ptr<sf::Shape> shape) : shape(std::move(shape)) {}

const sf::Vector2<float> Entity::get_position() {return position;}

void Entity::set_position(const sf::Vector2f& position) {
    this->position = position;
    shape->setPosition(sf::Vector2f(position));
}

void Entity::move(const sf::Vector2f& position) {this->position += position;}

void Entity::update(const float& delta_time) {
    shape->setPosition(sf::Vector2f(position));
}

void EntityManager::update(float delta_time) {
    for (std::shared_ptr<Entity> entity : EntityManager::list) {
        entity->update(delta_time);
    }
}

void EntityManager::render() {
    for (std::shared_ptr<Entity> entity : EntityManager::list) {
        entity->render();
    }
}