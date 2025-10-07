#include <memory>
#include <SFML/Graphics.hpp>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

sf::Texture GameSystem::spritesheet;
std::vector<std::shared_ptr<Ship>> GameSystem::ships;
bool GameSystem::invaders_hit_wall = false;

void GameSystem::init() {
    ships.push_back(std::make_shared<Player>());
    for (float row = 0; row < Parameters::rows; ++row) {
        sf::IntRect rect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(32, 32));
        for (float column = 0; column < Parameters::columns; ++column) {
            sf::Vector2f position = {(column * 32.0f) + 100, (row * 32.0f) + 100};
            std::shared_ptr<Invader> invader = std::make_shared<Invader>(rect, position);
            ships.push_back(invader);
        }
    }
    Bullet::init();
}

void GameSystem::update(const float& delta_time) {
    GameSystem::invaders_hit_wall = false;
    for (std::shared_ptr<Ship>& ship : ships) {
        ship->update(delta_time);
    }
    if (GameSystem::invaders_hit_wall) {
        Invader::move_all_down();
    }
    Bullet::update(delta_time);
}

void GameSystem::render(sf::RenderWindow &window) {
    for (const std::shared_ptr<Ship> &ship : ships) {
        window.draw(*(ship.get()));
    }
    Bullet::render(window);
}

void GameSystem::clean() {
    for (std::shared_ptr<Ship>& ship : ships) {
        ship.reset();  // Free up the memory of this shared pointer
    }
    ships.clear();  // Clear the vector to be sure we free up any memory left.
}