#include "ecm.hpp"
#include "entity.hpp"
#include "renderer.hpp"

Entity::Entity() {
    Entity::alive = true;
    Entity::for_deletion = false;
    Entity::visible = true;
}

Entity::~Entity() {}

void Entity::update(const float& delta_time) {
    for (std::shared_ptr<Component> component : Entity::components) {
        component->update(delta_time);
    }
}

void Entity::render() {
    for (std::shared_ptr<Component> component : Entity::components) {
        component->render();
    }
}

const sf::Vector2f& Entity::get_position() const {return position;}

void Entity::set_position(const sf::Vector2f& position) {
    this->position = position;
}

bool Entity::is_for_deletion() const {
    return Entity::for_deletion;
}

float Entity::get_rotation() const {
    return Entity::rotation;
}

void Entity::set_rotation(float rotation) {
    Entity::rotation = rotation;
}

bool Entity::is_alive() const {
    return Entity::alive;
}

void Entity::set_alive(bool alive) {
    Entity::alive = alive;
}

void Entity::set_for_delete() {
    Entity::for_deletion = true;
}

bool Entity::is_visible() const {
    return Entity::visible;
}

void Entity::set_visible(bool visible) {
    Entity::visible = visible;
}

Component::~Component() {}

Component::Component(Entity* const parent) : parent(parent) {}

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