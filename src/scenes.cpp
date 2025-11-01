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
        std::shared_ptr<Entity> box = std::make_shared<Entity>();
        std::shared_ptr<ShapeComponent> shape = box->add_component<ShapeComponent>();
        shape->set_shape<sf::RectangleShape>(sf::Vector2f(50.0f, 50.0f));
        shape->get_shape().setPosition(sf::Vector2f(i * (Parameters::game_width / 12.f), Parameters::game_height * .7f));
        shape->get_shape().setOrigin(sf::Vector2f(25.0f, 25.0f));
        shape->get_shape().setFillColor(sf::Color::White);
        entities.push_back(box);
        PhysicsScene::entity_manager.list.push_back(box);

        // Create a dynamic physics body for the box
        b2BodyId body = box2d::create_physics_box(world_id, true, std::static_pointer_cast<sf::RectangleShape>(shape->get_shape_ptr()));
        // Give the box a spin
        b2Body_ApplyAngularImpulse(body, 5.0f, true);
        bodies.push_back(body);
    }

    sf::Vector2f walls[] = {
        // Top
        sf::Vector2f(Parameters::game_width * 0.5f, 5.0f), sf::Vector2f(Parameters::game_width, 10.0f),
        // Bottom
        sf::Vector2f(Parameters::game_width * 0.5f, Parameters::game_height - 5.f), sf::Vector2f(Parameters::game_width, 10.0f),
        // Left
        sf::Vector2f(5.f, Parameters::game_height * 0.5f), sf::Vector2f(10.0f, Parameters::game_height),
        // Right
        sf::Vector2f(Parameters::game_width - 5.0f, Parameters::game_height * 0.5f), sf::Vector2f(10.0f, Parameters::game_height)
    };

    // Build Walls
    for (int i = 0; i < 7; i += 2) {
        // Create SFML shapes for each wall
        std::shared_ptr<Entity> box = std::make_shared<Entity>();
        std::shared_ptr<ShapeComponent> shape = box->add_component<ShapeComponent>();
        sf::Vector2f wall_size = walls[i + 1];
        shape->set_shape<sf::RectangleShape>(wall_size);
        shape->get_shape().setOrigin(wall_size.x * 0.5f, wall_size.y * 0.5f);
        shape->get_shape().setPosition(walls[i]);
        shape->get_shape().setFillColor(sf::Color::White);
        entities.push_back(box);
        PhysicsScene::entity_manager.list.push_back(box);
        // Create a static physics body for the wall
        b2BodyId body = box2d::create_physics_box(world_id, false, std::static_pointer_cast<sf::RectangleShape>(shape->get_shape_ptr()));
        bodies.push_back(body);
    }
}

void PhysicsScene::update(const float& delta_time) {
    Scene::update(delta_time);
    // Step Physics world by time_step
    b2World_Step(world_id, Parameters::time_step, Parameters::sub_step_count);
    for (int i = 0; i < bodies.size(); ++i) {
        // Sync Sprites to physics position
        entities[i]->set_position(box2d::invert_height(box2d::bv2_to_sv2(b2Body_GetPosition(bodies[i]))));
        // Sync Sprites to physics Rotation
        b2Rot rotation = b2Body_GetRotation(bodies[i]);
        float angle_radians = atan2(rotation.s, rotation.c);
        entities[i]->set_rotation(angle_radians * (180.0f / Parameters::pi));
    }
}

void PhysicsScene::render() {
    Scene::render();
}

void PhysicsScene::unload() {
    Scene::unload();
    b2DestroyWorld(this->world_id);
    bodies.clear();
}