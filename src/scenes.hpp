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

class EndScene : public Scene {
    public:
        EndScene() = default;
        void load() override;
        void render(sf::RenderWindow& window) override;
    private:
        sf::Text win_text;
        sf::Font font;
};

struct Scenes {
    static std::shared_ptr<Scene> maze;
    static std::shared_ptr<Scene> end;
};