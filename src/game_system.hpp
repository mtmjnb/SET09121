#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "ship.hpp"

struct GameSystem {
    //The global variables goes here
    static sf::Texture spritesheet;
    static std::vector<std::shared_ptr<Ship>> ships;  // vector of shared pointers to Ships
    static bool invaders_hit_wall;
    static bool playing;

    // Game system functions
    static void init();
    static void clean();
    static void update(const float& delta_time);
    static void render(sf::RenderWindow& window);
};