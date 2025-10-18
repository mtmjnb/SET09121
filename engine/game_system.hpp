#pragma once
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "ecm.hpp"

class Scene {
    public:
        Scene() = default;
        virtual void load() = 0;
        std::vector<std::shared_ptr<Entity>>& get_entities() {return entity_manager.list;}

        virtual void update(const float& delta_time);  // Update all entities in the scene
        virtual void render();  // Render all entities in the scene
        
        virtual void unload();
        virtual ~Scene() = default;

    protected:
        EntityManager entity_manager;
};

class GameSystem {
    public:
        static void start(unsigned int width, unsigned int height, const std::string& name, const float& time_step);  // Start the game
        static void clean();
        static void reset();
        static void set_active_scene(const std::shared_ptr<Scene>& active_scene);
        static std::shared_ptr<Scene> get_active_scene();

    private:
        static void init();
        static void update(const float& delta_time);
        static void render();
        static std::shared_ptr<Scene> active_scene;
};