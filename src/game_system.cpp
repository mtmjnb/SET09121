#include <SFML/Graphics.hpp>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "scenes.hpp"

void Scene::update(const float& delta_time) {
    for (std::shared_ptr<Entity>& entity : entities) {
        entity->update(delta_time);
    }
}

void Scene::render(sf::RenderWindow& window) {
    for (std::shared_ptr<Entity>& entity : entities) {
        entity->render(window);
    }
}

void Scene::unload() {}

std::shared_ptr<Scene> GameSystem::active_scene = std::make_shared<MazeScene>();

void GameSystem::init() {}

void GameSystem::update(const float& delta_time) {
    GameSystem::active_scene->update(delta_time);
}

void GameSystem::render(sf::RenderWindow &window) {
    GameSystem::active_scene->render(window);
}

void GameSystem::clean() {}

void GameSystem::start(unsigned int width, unsigned int height, const std::string& name, const float& time_step) {
    sf::RenderWindow window(sf::VideoMode({width, height}), name);
    GameSystem::init();
    sf::Event event;
    while (window.isOpen()) {
        static sf::Clock clock;
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                clean();
                return;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        window.clear();
        update(dt);
        render(window);
        sf::sleep(sf::seconds(time_step));
        //Wait for Vsync
        window.display();
    }
    window.close();
    clean();
}

void GameSystem::set_active_scene(const std::shared_ptr<Scene>& active_scene) {
    GameSystem::active_scene = active_scene;
}