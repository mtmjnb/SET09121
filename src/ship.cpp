#include <iostream>
#include "ship.hpp"
#include "game_system.hpp"
#include "game_parameters.hpp"

float Ship::drop_distance = 16.0f;

Ship::Ship() {};

Ship::Ship(const Ship& sprite) :
    _sprite(sprite._sprite) {}

Ship::Ship(sf::IntRect int_rect) : Sprite() {
    _sprite = int_rect;
    if (!GameSystem::spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    setTexture(GameSystem::spritesheet);
    setTextureRect(_sprite);
};

void Ship::update(const float& delta_time) {}

// Define the ship deconstructor. Although we set this to pure virtual, we still have to define it
Ship::~Ship() = default;

// ======================================== Invader ========================================

bool Invader::direction = true;
float Invader::speed = 100.0f;
float Invader::acceleration = 1.0f;

Invader::Invader() : Ship() {}
Invader::Invader(const Invader& invader) : Ship(invader) {}
Invader::Invader(sf::IntRect int_rect, sf::Vector2f position) : Ship(int_rect) {
    setOrigin(sf::Vector2f(16.f, 16.f));;
    setPosition(position);
}

void Invader::update(const float& delta_time) {
    Ship::update(delta_time);

    move(delta_time * (direction ? 1.0f : -1.0f) * speed, 0.0f);

    if ((direction && getPosition().x > Parameters::game_width - Parameters::sprite_size / 2.f) || (!direction && getPosition().x < Parameters::sprite_size / 2.f)) {
        GameSystem::invaders_hit_wall = true;
    }
}

void Invader::move_all_down() {
    direction = !direction;
    speed += Invader::acceleration;
    for (std::shared_ptr<Ship>& ship : GameSystem::ships) {
        // Move down
        ship->move({ 0.0f, Ship::drop_distance });
    }
}