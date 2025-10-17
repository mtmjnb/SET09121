#include "game_parameters.hpp"
#include "engine/game_system.hpp"
#include "scenes.hpp"

int main() {
    Scenes::menu = std::make_shared<MenuScene>();
    Scenes::menu->load();
    Scenes::game = std::make_shared<GameScene>();
    Scenes::game->load();
    GameSystem::set_active_scene(Scenes::menu);
    GameSystem::start(Parameters::game_width, Parameters::game_height, "pacman", Parameters::time_step);
    return 0;
}