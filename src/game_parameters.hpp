#pragma once
#include <SFML/Graphics.hpp>

struct Parameters {
    static constexpr int game_width = 1280;
    static constexpr int game_height = 720;
    static constexpr float time_step = 0.017f; // 60 fps
    static constexpr float gravity = -9.82f;
    static constexpr float physics_scale = 30.0f;  // 30 pixels = 1 meter
    static constexpr float physics_scale_inv = 1.0f / physics_scale;
    static constexpr float pi = 3.14;
    static constexpr int sub_step_count = 3;
};