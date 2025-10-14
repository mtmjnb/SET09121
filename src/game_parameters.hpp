#pragma once
#include <SFML/Graphics.hpp>

struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr float time_step = 0.017f; // 60 fps
    static constexpr sf::Keyboard::Key controls[8] = {
        sf::Keyboard::W,  // Player Up
        sf::Keyboard::A,  // Player Left
        sf::Keyboard::S,  // Player Down
        sf::Keyboard::D,  // Player Right
        sf::Keyboard::Up,  // Player Up
        sf::Keyboard::Left,  // Player Left
        sf::Keyboard::Down,  // Player Left
        sf::Keyboard::Right,  // Player Right
    };
    static constexpr const char* maze_1 = "res/levels/maze.txt";
    static constexpr const char* maze_2 = "res/levels/maze_2.txt";
    static constexpr const char* maze_3 = "res/levels/maze_3.txt";
    static constexpr const char* maze_4 = "res/levels/maze_4.txt";
    static constexpr const char* maze_5 = "res/levels/maze_5.txt";
    static constexpr float player_speed = 400.f;
};