#include <iostream>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "bullet.hpp"

unsigned char Bullet::bulletPointer;
Bullet Bullet::bullets[256];

Bullet::Bullet() {}

void Bullet::update(const float& delta_time) {
    for (Bullet& bullet : Bullet::bullets) {
        bullet._update(delta_time);
    }
}

void Bullet::render(sf::RenderWindow& window) {
    for (Bullet bullet : Bullet::bullets) {
        window.draw(bullet);
    }
}

void Bullet::fire(const sf::Vector2f& posistion, const bool mode) {
    Bullet& bullet = bullets[++bulletPointer];
    if (mode) {
        bullet.setTextureRect(sf::IntRect({Parameters::sprite_size * 1, Parameters::sprite_size * 1}, {Parameters::sprite_size, Parameters::sprite_size}));
    } else {
        bullet.setTextureRect(sf::IntRect({Parameters::sprite_size * 2, Parameters::sprite_size * 1}, {Parameters::sprite_size, Parameters::sprite_size}));
    }
    bullet.setPosition(posistion);
    bullet.mode = mode;
}
void Bullet::init() {
    for (int i = 0; i < 256; i++) {
        bullets[i].setTexture(GameSystem::spritesheet);
        bullets[i].setOrigin(Parameters::sprite_size / 2.f, Parameters::sprite_size / 2.f);
        bullets[i].setPosition(-100, -100);
    }
}

void Bullet::_update(const float& delta_time) {
    if (getPosition().y < -Parameters::sprite_size || getPosition().y > Parameters::game_height + Parameters::sprite_size) {
        //off screen - do nothing
        return;
    }

    move(sf::Vector2f(0, delta_time * Parameters::bullet_speed * (mode ? -1.0f : 1.0f)));
    const sf::FloatRect bounding_box = getGlobalBounds();
    std::shared_ptr<Ship>& player = GameSystem::ships[0]; // We know that the first ship is the player
    for (std::shared_ptr<Ship>& ship : GameSystem::ships) {
        if (mode && ship == player) {
            // Player bullets don't collide with player
            continue;
        }
        if (!mode && ship != player) {
            // Invader bullets don't collide with other invaders
            continue;
        }
        if (!ship->is_exploded() &&
            ship->getGlobalBounds().intersects(bounding_box)) {
            ship->explode();
            setPosition(sf::Vector2f(-100, -100));  // Warp bullet off-screen
            if (ship == player) {
                std::cout << "You Died :(" << std::endl;
                GameSystem::playing = false;
            }
            return;
        }
    }
}