#include "scenes.hpp"
#include "game_parameters.hpp"
#include "player.hpp"

std::shared_ptr<Scene> Scenes::maze;

void MazeScene::load() {
    std::shared_ptr<Entity> player = std::make_shared<Player>();
    entities.push_back(player);
    reset();

}
void MazeScene::reset() {
    entities[0]->set_position(sf::Vector2f(Parameters::game_width / 2, Parameters::game_height / 2));
}

void MazeScene::update(const float& delta_time) {
    Scene::update(delta_time);
}

void MazeScene::render(sf::RenderWindow& window) {
    Scene::render(window);
}

void MazeScene::set_file_path(const std::string& file_path) {}