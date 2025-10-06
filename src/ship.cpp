#include <iostream>
#include <SFML/Graphics.hpp>
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
        if (ship != std::dynamic_pointer_cast<Invader>(ship)) {
            continue;
        }
        // Move down
        ship->move({ 0.0f, Ship::drop_distance });
    }
}

// ======================================== Player ========================================
Player::Player() :
    Ship(sf::IntRect(sf::Vector2i(Parameters::sprite_size * 5, Parameters::sprite_size),
        sf::Vector2i(Parameters::sprite_size, Parameters::sprite_size))) {
    setOrigin(Parameters::sprite_size / 2.f, Parameters::sprite_size / 2.f);
    setPosition(Parameters::game_width / 2.f, Parameters::game_height - static_cast<float>(Parameters::sprite_size));
}

void Player::update(const float& dt) {
    Ship::update(dt);
    //Move left
    float direction = 0.0f;
    if (sf::Keyboard::isKeyPressed(Parameters::controls[0]) || sf::Keyboard::isKeyPressed(Parameters::controls[2])) {
        direction--;
    }
    if (sf::Keyboard::isKeyPressed(Parameters::controls[1]) || sf::Keyboard::isKeyPressed(Parameters::controls[3])) {
        direction++;
    }
    this->move(sf::Vector2f(direction * Parameters::player_speed * dt, 0.f));

    //Move Right

}