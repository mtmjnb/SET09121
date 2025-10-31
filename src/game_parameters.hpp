#pragma once
#include <SFML/Graphics.hpp>

struct Parameters {
    static constexpr int game_width = 1280;
    static constexpr int game_height = 720;
    static constexpr float time_step = 0.017f; // 60 fps
    static constexpr float gravity = -9.82f;
};