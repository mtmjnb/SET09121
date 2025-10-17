#include <queue>
#include "renderer.hpp"

static std::queue<const sf::Drawable*> sprites;

void Renderer::initialise(sf::RenderWindow& render_window) {
    Renderer::render_window = &render_window;
}

sf::RenderWindow& Renderer::get_window() { return *Renderer::render_window; }

void Renderer::shutdown() {
    while (!sprites.empty()) {
        sprites.pop();
    }
}

void Renderer::update(const float& delta_time) {}

void Renderer::render() {
    if (Renderer::render_window == nullptr) {
        throw("No render window set! ");
    }
    while (!sprites.empty()) {
        Renderer::render_window->draw(*sprites.front());
        sprites.pop();
    }
}

void Renderer::queue(const sf::Drawable* sprite) { sprites.push(sprite); }