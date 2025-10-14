#include <iostream>
#include "tile_level_loader/level_system.hpp"
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "player.hpp"

std::shared_ptr<Scene> Scenes::maze;
std::shared_ptr<Scene> Scenes::end;

void MazeScene::load() {
    std::shared_ptr<Entity> player = std::make_shared<Player>();
    entities.push_back(player);
    reset();

}
void MazeScene::reset() {
    LevelSystem::load_level(MazeScene::file_path);
    entities[0]->set_position(LevelSystem::get_start_position() + sf::Vector2f(LevelSystem::get_tile_size() / 2.0f, LevelSystem::get_tile_size() / 2.0f));  // Move shape to center of the start posistion tile
}

void MazeScene::update(const float& delta_time) {
    Scene::update(delta_time);
    if (LevelSystem::get_tile_at(entities[0]->get_position()) == LevelSystem::END) {
        if (MazeScene::file_path == std::string(Parameters::maze_1)) {
            MazeScene::file_path = Parameters::maze_2;
            reset();
        } else if (MazeScene::file_path == std::string(Parameters::maze_2)) {
            MazeScene::file_path = Parameters::maze_3;
            reset();
        } else if (MazeScene::file_path == std::string(Parameters::maze_3)) {
            MazeScene::file_path = Parameters::maze_4;
            reset();
        } else if (MazeScene::file_path == std::string(Parameters::maze_4)) {
            MazeScene::file_path = Parameters::maze_5;
            reset();
        } else if (MazeScene::file_path == std::string(Parameters::maze_5)) {
            unload();  // Unload the maze scene
            GameSystem::set_active_scene(Scenes::end);  // Switch the active scene to the end scene
        }
        return;
    }
}

void MazeScene::render(sf::RenderWindow& window) {
    Scene::render(window);
    LevelSystem::render(window);
}

void MazeScene::set_file_path(const std::string& file_path) {
    MazeScene::file_path = file_path;
}

void EndScene::load() {}

void EndScene::render(sf::RenderWindow& window) {}