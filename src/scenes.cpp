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
}

void GameScene::load() {
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
    this->text.setFont(font);
    this->text.setCharacterSize(24);
    this->text.setPosition((Parameters::game_width * .5f) - (this->text.getLocalBounds().width * .5f), 0);

    std::shared_ptr<Entity> player = std::make_shared<Entity>();
    std::shared_ptr<ShapeComponent> shape = player->add_component<ShapeComponent>();
    shape->set_shape<sf::CircleShape>(Parameters::entity_size);
    shape->get_shape().setFillColor(sf::Color::Yellow);
    shape->get_shape().setOrigin(sf::Vector2f(Parameters::entity_size, Parameters::entity_size));
    GameScene::entity_manager.list.push_back(player);

    const sf::Color ghost_colors[]{ {208, 62, 25},  // Red Blinky
                                 {219, 133, 28},  // Orange Clyde
                                 {70, 191, 238},  // Cyan Inky
                                 {234, 130, 229} };  // Pink Pinky

    for (int i = 0; i < std::size(ghost_colors); i++) {
        std::shared_ptr<Entity> ghost = std::make_shared<Entity>();
        std::shared_ptr<ShapeComponent> shape = ghost->add_component<ShapeComponent>();
        shape->set_shape<sf::CircleShape>(Parameters::entity_size);
        shape->get_shape().setFillColor(ghost_colors[i % std::size(ghost_colors)]);
        shape->get_shape().setOrigin(
            sf::Vector2f(Parameters::entity_size, Parameters::entity_size));
        GameScene::entity_manager.list.push_back(ghost);
    }
}

void GameScene::respawn() {

}