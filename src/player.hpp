#pragma once
#include "entity.hpp"

class Player : public Entity {
    public:
        void update(const float& delta_time) override;
        Player();
        void render(sf::RenderWindow& window) const override;

    private:
        static constexpr float radius = 25.f;
        static constexpr float speed = 200.f;
        bool valid_move(sf::Vector2f position);
};