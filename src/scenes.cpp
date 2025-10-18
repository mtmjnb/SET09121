#include <iostream>
#include "engine/tile_level_loader/level_system.hpp"
#include "engine/renderer.hpp"
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "components.hpp"

// ================================ Scenes ================================

std::shared_ptr<Scene> Scenes::menu;
std::shared_ptr<Scene> Scenes::game;

// ================================ MenuScene ================================

void MenuScene::update(const float& delta_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        GameSystem::set_active_scene(Scenes::game);
    }
    Scene::update(delta_time);
    this->text.setString("Almost Pacman");
    this->text.setPosition((Parameters::game_width * .5f) - (this->text.getLocalBounds().width * .5f), 0);
}

void MenuScene::render() {
    Renderer::queue(&text);
    Scene::render();
}

void MenuScene::load() {
    // Set up the text element here!
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
    this->text.setFont(font);
    this->text.setCharacterSize(24);
}

// ================================ GameScene ================================

void GameScene::update(const float& delta_time) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        GameSystem::set_active_scene(Scenes::menu);
    }
    Scene::update(delta_time);
}

void GameScene::render() {
    Renderer::queue(&text);
    Scene::render();
    LevelSystem::render();
}

void GameScene::load() {
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
    this->text.setFont(font);
    this->text.setCharacterSize(24);
    this->text.setPosition((Parameters::game_width * .5f) - (this->text.getLocalBounds().width * .5f), 0);

    LevelSystem::load_level(Parameters::pacman, 25.0f);

    this->player = std::make_shared<Entity>();
    std::shared_ptr<ShapeComponent> shape = this->player->add_component<ShapeComponent>();
    shape->set_shape<sf::CircleShape>(Parameters::entity_size);
    shape->get_shape().setFillColor(sf::Color::Yellow);
    shape->get_shape().setOrigin(sf::Vector2f(Parameters::entity_size, Parameters::entity_size));
    this->player->add_component<PlayerMovementComponent>();
    GameScene::entity_manager.list.push_back(this->player);

    const sf::Color ghost_colors[]{ {208, 62, 25},  // Red Blinky
                                 {219, 133, 28},  // Orange Clyde
                                 {70, 191, 238},  // Cyan Inky
                                 {234, 130, 229} };  // Pink Pinky

    for (int i = 0; i < std::size(ghost_colors); ++i) {
        std::shared_ptr<Entity> ghost = std::make_shared<Entity>();
        std::shared_ptr<ShapeComponent> shape = ghost->add_component<ShapeComponent>();
        shape->set_shape<sf::CircleShape>(Parameters::entity_size);
        shape->get_shape().setFillColor(ghost_colors[i % std::size(ghost_colors)]);
        shape->get_shape().setOrigin(
            sf::Vector2f(Parameters::entity_size, Parameters::entity_size));
        ghost->add_component<EnemyAIComponent>();
        GameScene::entity_manager.list.push_back(ghost);
    }

    GameScene::respawn();
}

void GameScene::respawn() {
    this->player->set_position(LevelSystem::get_start_position());
    this->player->get_compatible_components<ActorMovementComponent>()[0]
        ->set_speed(Parameters::player_speed);

    std::vector<sf::Vector2i> ghost_spawns = LevelSystem::find_tiles(LevelSystem::ENEMY);
    for (size_t i = 1; i < GameScene::entity_manager.list.size(); i++) {
        std::shared_ptr<Entity>& ghost = GameScene::entity_manager.list[i];
        ghost->set_position(
            LevelSystem::get_tile_position(ghost_spawns[rand() % ghost_spawns.size()]));
        ghost->get_compatible_components<ActorMovementComponent>()[0]->set_speed(Parameters::ghost_speed);
    }
}