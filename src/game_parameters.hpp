#pragma once
#include <SFML/Graphics.hpp>

struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr float time_step = 0.017f; // 60 fps
    static constexpr const char* pacman = "res/levels/pacman.txt";
    static constexpr float player_speed = 400.f;
    static constexpr float entity_size = 16.0f;
};