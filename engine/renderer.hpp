#pragma once
#include <SFML/Graphics.hpp>

namespace Renderer {
    void initialise(sf::RenderWindow& render_window);
    sf::RenderWindow& get_window();

    void shutdown();
    void update(const float& delta_time);
    void queue(const sf::Drawable* sprite);
    void render();

    static sf::RenderWindow* render_window;
};