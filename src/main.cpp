#include "game_parameters.hpp"
#include "engine/game_system.hpp"
#include "scenes.hpp"

int main() {
    Scenes::physicsScene = std::make_shared<PhysicsScene>();
    Scenes::physicsScene->load();
    GameSystem::set_active_scene(Scenes::physicsScene);
    GameSystem::start(Parameters::game_width, Parameters::game_height, "Physics", Parameters::time_step);
    return 0;
}