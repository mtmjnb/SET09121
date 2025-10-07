#pragma once

struct Parameters {
    static constexpr int game_width = 800;
    static constexpr int game_height = 600;
    static constexpr int sprite_size = 32;
    static constexpr int rows = 5;
    static constexpr int columns = 11;
    static constexpr float time_step = 0.017f; // 60 fps
    static constexpr sf::Keyboard::Key controls[7] = {
        sf::Keyboard::A,  // Player Left
        sf::Keyboard::D,  // Player Right
        sf::Keyboard::Left,  // Player Left
        sf::Keyboard::Right,  // Player Right
        sf::Keyboard::W,  // Player shoot
        sf::Keyboard::Up,  // Player shoot
        sf::Keyboard::Space  // Player shoot
    };
    static constexpr float player_speed = 400.f;
    static constexpr float bullet_speed = 400.0f;
};