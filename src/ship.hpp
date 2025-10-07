#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
    public:
        static float drop_distance;
        Ship();
        Ship(const Ship& ship);  // Copy constructor
        Ship(sf::IntRect int_rect);  // Constructor that takes a sprite
        virtual ~Ship() = 0;  // Pure virtual deconstructor - makes this an abstract class and avoids undefined behaviour!
        virtual void update(const float& delta_time);  // Update, virtual so can be overridden, but not pure virtual
        bool is_exploded() const;
        virtual void explode();
    protected:
        sf::IntRect sprite;
        bool exploded = false;
};

class Invader : public Ship {
    public:
        Invader();
        Invader(const Invader& invader);
        Invader(sf::IntRect int_rect, sf::Vector2f position);
        void update(const float& delta_time) override;
        static void move_all_down();
    private:
        static bool direction;
        static float speed;
        static float acceleration;
};

class Player : public Ship {
    public:
        Player();
        void update(const float& dt) override;
};