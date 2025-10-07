#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
    static void update(const float& delta_time);  // Updates all bullets (by calling _Update() on all bullets in the pool)
    static void render(sf::RenderWindow& window);  // Render's all bullets (uses a similar trick to the ship renderer but on the bullet pool)
    static void fire(const sf::Vector2f& posistion, const bool mode);  // Chose an inactive bullet and use it
    static void init();  // Set all the bullets to -100, -100, set the spritesheet, set origin
    ~Bullet() = default;
protected:
    Bullet();
    bool mode;  // true=player bullet, false=Enemy bullet
    void _update(const float& dt);  // Called by the static Update()
    static unsigned char bulletPointer;
    static Bullet bullets[256];
};