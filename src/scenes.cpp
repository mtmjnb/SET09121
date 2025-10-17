#include <iostream>
#include "engine/tile_level_loader/level_system.hpp"
#include "engine/renderer.hpp"
#include "scenes.hpp"
#include "game_parameters.hpp"
#include "player.hpp"

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
}

void GameScene::respawn() {

}