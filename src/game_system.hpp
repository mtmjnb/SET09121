#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"

class Scene {
    public:
        Scene() = default;
        virtual void load() = 0;
        std::vector<std::shared_ptr<Entity>>& get_entities() {return entities;}

        virtual void update(const float& delta_time);  // Update all entities in the scene
        virtual void render(sf::RenderWindow& window);  // Render all entities in the scene
        
        virtual void unload();
        virtual ~Scene() = default;

    protected:
        std::vector<std::shared_ptr<Entity>> entities;
};

class GameSystem {
    public:
        static void start(unsigned int width, unsigned int height, const std::string& name, const float& time_step);  // Start the game
        static void clean();
        static void reset();
        static void set_active_scene(const std::shared_ptr<Scene>& active_scene);

    private:
        static void init();
        static void update(const float& delta_time);
        static void render(sf::RenderWindow& window);
        static std::shared_ptr<Scene> active_scene;
};