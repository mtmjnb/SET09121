#include "game_parameters.hpp"
#include "engine/game_system.hpp"
#include "scenes.hpp"

int main() {
    Scenes::physics = std::make_shared<PhysicsScene>();
    Scenes::physics->load();
    GameSystem::set_active_scene(Scenes::physics);
    GameSystem::start(Parameters::game_width, Parameters::game_height, "Physics", Parameters::time_step);
    return 0;
}