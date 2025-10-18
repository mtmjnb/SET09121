#include "engine/renderer.hpp"
#include "components.hpp"

void ShapeComponent::update(const float& delta_time) {
    shape->setPosition(parent->get_position());
}

void ShapeComponent::render() { Renderer::queue(shape.get()); }

sf::Shape& ShapeComponent::get_shape() const { return *shape; }

ShapeComponent::ShapeComponent(Entity* parent) : Component(parent), shape(std::make_shared<sf::CircleShape>()) {}
