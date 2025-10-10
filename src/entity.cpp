#include "entity.hpp"

Entity::Entity(std::unique_ptr<sf::Shape> shape) : shape(std::move(shape)) {}

const sf::Vector2f Entity::get_position() {return position;}

void Entity::set_position(const sf::Vector2f& position) {
    this->position = position;
    shape->setPosition(sf::Vector2f(position));
}

void Entity::move(const sf::Vector2f& position) {this->position += position;}

void Entity::update(const float& delta_time) {
    shape->setPosition(sf::Vector2f(position));
}