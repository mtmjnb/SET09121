#include <iostream>
#include "engine/tile_level_loader/level_system.hpp"
#include "engine/renderer.hpp"
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "components.hpp"

// ================================================================ Scenes ================================================================

std::shared_ptr<Scene> Scenes::physicsScene;

// ================================================================ PhysicsScene ================================================================

void PhysicsScene::load() {
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = b2Vec2({ 0.0f, Parameters::gravity });
    this->world_id = b2CreateWorld(&world_def);
}

void PhysicsScene::update(const float& delta_time) {
    Scene::update(delta_time);
}

void PhysicsScene::render() {
    Scene::render();
}

void PhysicsScene::unload() {
    Scene::unload();
    b2DestroyWorld(this->world_id);
}