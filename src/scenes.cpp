#include <iostream>
#include "engine/tile_level_loader/level_system.hpp"
#include "engine/renderer.hpp"
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "components.hpp"
#include "b2d_utils.hpp"

// ================================================================ Scenes ================================================================

std::shared_ptr<Scene> Scenes::physics;

// ================================================================ PhysicsScene ================================================================

void PhysicsScene::load() {
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = b2Vec2({ 0.0f, Parameters::gravity });
    this->world_id = b2CreateWorld(&world_def);

    // Create Boxes
    for (int i = 1; i < 11; ++i) {
        // Create SFML shapes for each box
        std::shared_ptr<sf::RectangleShape> shape = std::make_shared<sf::RectangleShape>();
        shape->setPosition(sf::Vector2f(i * (Parameters::game_width / 12.f), Parameters::game_height * .7f));
        shape->setSize(sf::Vector2f(50.0f, 50.0f));
        shape->setOrigin(sf::Vector2f(25.0f, 25.0f));
        shape->setFillColor(sf::Color::White);
        sprites.push_back(shape);


        // Create a dynamic physics body for the box
        b2BodyId body = box2d::create_physics_box(world_id, true, shape);
        // Give the box a spin
        b2Body_ApplyAngularImpulse(body, 5.0f, true);
        bodies.push_back(body);
    }
}

void PhysicsScene::update(const float& delta_time) {
    Scene::update(delta_time);
    // Step Physics world by time_step
    b2World_Step(world_id, Parameters::time_step, Parameters::sub_step_count);
    for (int i = 0; i < bodies.size(); ++i) {
        // Sync Sprites to physics position
        sprites[i]->setPosition(box2d::invert_height(box2d::bv2_to_sv2(b2Body_GetPosition(bodies[i]))));
        // Sync Sprites to physics Rotation
        sprites[i]->setRotation((180 / Parameters::pi) * asin(b2Body_GetRotation(bodies[i]).s));
    }
}

void PhysicsScene::render() {
    Scene::render();
    for (std::shared_ptr<sf::RectangleShape> sprite : this->sprites) {
        Renderer::queue(&(*sprite));
    }
}

void PhysicsScene::unload() {
    Scene::unload();
    b2DestroyWorld(this->world_id);
    bodies.clear();
}