#pragma once
#include <string>
#include "game_system.hpp"

class MazeScene : public Scene {
    public:
        MazeScene() = default;
        void load() override;  // Loads entities

        void update(const float& delta_time) override;  // Update Scene
        void render(sf::RenderWindow& window) override;  // Render Maze Scene
        void reset();  // Loads level and resets entities

        void set_file_path(const std::string& file_path);
    private:
        std::string file_path;
};

struct Scenes {
    static std::shared_ptr<Scene> maze;
};