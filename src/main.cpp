#include "game_parameters.hpp"
#include "game_system.hpp"
#include "scenes.hpp"

int main() {
    Scenes::maze = std::make_shared<MazeScene>();
    std::static_pointer_cast<MazeScene>(Scenes::maze)->set_file_path(Parameters::maze_1);
    Scenes::maze->load();
    GameSystem::set_active_scene(Scenes::maze);
    GameSystem::start(Parameters::game_width, Parameters::game_height, "tile_maze", Parameters::time_step);
    return 0;
}