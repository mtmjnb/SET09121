#include <SFML/Graphics.hpp>
#include "game_system.hpp"
#include "renderer.hpp"

void Scene::update(const float& delta_time) {
    Renderer::update(delta_time);
    for (std::shared_ptr<Entity>& entity : entity_manager.list) {
        entity->update(delta_time);
    }
    
    // Remove all entities marked for deletion
    auto new_end = std::remove_if(
        entity_manager.list.begin(),
        entity_manager.list.end(),
        [](const std::shared_ptr<Entity>& entity) {
            return entity->is_for_deletion();
        }
    );
    entity_manager.list.erase(new_end, entity_manager.list.end());
}

void Scene::render() {
    for (std::shared_ptr<Entity>& entity : entity_manager.list) {
        entity->render();
    }
}

void Scene::unload() {}

std::shared_ptr<Scene> GameSystem::active_scene;

void GameSystem::init() {}

void GameSystem::update(const float& delta_time) {
    GameSystem::active_scene->update(delta_time);
}

void GameSystem::render() {
    GameSystem::active_scene->render();
}

void GameSystem::clean() {}

void GameSystem::start(unsigned int width, unsigned int height, const std::string& name, const float& time_step) {
    sf::RenderWindow window(sf::VideoMode({width, height}), name);
    Renderer::initialise(window);
    GameSystem::init();
    sf::Event event;
    while (window.isOpen()) {
        static sf::Clock clock;
        float delta_time = clock.restart().asSeconds();
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
        update(delta_time);
        render();
        Renderer::render();
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

std::shared_ptr<Scene> GameSystem::get_active_scene() {
    return GameSystem::active_scene;
}