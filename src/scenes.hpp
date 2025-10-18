#pragma once
#include "engine\game_system.hpp"

auto vector_distance = [](sf::Vector2f point1, sf::Vector2f point2) -> float {
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + (point1.y - point2.y) * (point1.y - point2.y));
};

struct Scenes {
    static std::shared_ptr<Scene> menu;
    static std::shared_ptr<Scene> game;
};

class MenuScene : public Scene {
    public:
        MenuScene() = default;
        void update(const float& delta_time) override;
        void render() override;
        void load() override;
    private:
        sf::Text text;
        sf::Font font;
};

class GameScene : public Scene {
    public:
        GameScene() = default;
        void update(const float& delta_time) override;
        void render() override;
        void load() override;

    private:
        std::shared_ptr<Entity> player;
        std::vector<std::shared_ptr<Entity>> ghosts;
        sf::Text text;
        sf::Font font;
        sf::Clock scoreClock;
        EntityManager nibbles;
        std::shared_ptr<Entity> _make_nibble(const sf::Vector2i& position, bool big);
        void respawn();
};