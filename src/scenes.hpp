#pragma once
#include <box2d/box2d.h>
#include "engine\game_system.hpp"

auto vector_distance = [](sf::Vector2f point1, sf::Vector2f point2) -> float {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
};

struct Scenes {
    static std::shared_ptr<Scene> physics;
};

class PhysicsScene : public Scene {
public:
    PhysicsScene() = default;
    void update(const float& dt) override;
    void render() override;
    void load()override;
    void unload() override;
private:
    b2WorldId world_id;  // An id to the physic world
    std::vector<b2BodyId> bodies;
    std::vector<std::shared_ptr<Entity>> entities;
};
