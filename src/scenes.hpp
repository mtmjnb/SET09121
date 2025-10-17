#pragma once
#include "engine\game_system.hpp"

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
        sf::Text text;
        sf::Font font;
        sf::Clock scoreClock;
        void respawn();
};