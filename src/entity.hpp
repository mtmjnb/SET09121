#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Entity {
    public:
        Entity(std::unique_ptr<sf::Shape> shape);
        Entity() = delete;
        virtual ~Entity() = default;

        virtual void update(const float& delta_time);
        virtual void render(sf::RenderWindow& window) const = 0;

        const sf::Vector2f get_position();
        void set_position(const sf::Vector2f& position);
        void move(const sf::Vector2f& position);

    protected:
        std::unique_ptr<sf::Shape> shape;
        sf::Vector2f position;
};