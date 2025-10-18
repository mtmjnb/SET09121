#pragma once
#include "engine/ecm.hpp"

class ShapeComponent : public Component {
    public:
        ShapeComponent() = delete;
        explicit ShapeComponent(Entity* const parent);

        void update(const float& delta_time) override;
        void render() override;

        sf::Shape& get_shape() const;

        template <typename T, typename... Targs> void set_shape(Targs... params) {
            shape.reset(new T(params...));
        }
    protected:
        std::shared_ptr<sf::Shape> shape;
};

class ActorMovementComponent : public Component {
    public:
        explicit ActorMovementComponent(Entity* parent);
        ActorMovementComponent() = delete;

        float get_speed() const;
        void set_speed(float speed);

        void move(const sf::Vector2f&);
        void move(float x, float y);

        void render() override {}
        void update(const float& delta_time) override;
    protected:
        bool valid_move(const sf::Vector2f&);
        float speed;
};

class PlayerMovementComponent : public ActorMovementComponent {
    public:
        PlayerMovementComponent(Entity* parent);
        void update(const float& delta_time) override;
};

class EnemyAIComponent : public ActorMovementComponent {
    public:
        EnemyAIComponent(Entity* parent);
        void update(const float& delta_time) override;
    protected:
        sf::Vector2f direction;
        enum state { ROAMING, ROTATING, ROTATED };
        state state;
};