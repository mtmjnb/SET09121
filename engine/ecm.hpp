#pragma once
#include <cmath>
#include <algorithm>
#include <memory>
#include <typeindex>
#include <vector>
#include <SFML/Graphics.hpp>

class Component;

class Entity {
    public:
        Entity();
        virtual ~Entity();
        virtual void update(const float& delta_time);
        virtual void render();

        const sf::Vector2f& get_position() const;
        void set_position(const sf::Vector2f& position);
        bool is_for_deletion() const;
        float get_rotation() const;
        void set_rotation(float rotation);
        bool is_alive() const;
        void set_alive(bool alive);
        void set_for_delete();
        bool is_visible() const;
        void set_visible(bool visible);

        template <typename T, typename... Targs> std::shared_ptr<T> add_component(Targs... params) {
            static_assert(std::is_base_of<Component, T>::value, "T != component");
            std::shared_ptr<T> component(std::make_shared<T>(this, params...));
            components.push_back(component);
            return component;
        }
    protected:
        std::vector<std::shared_ptr<Component>> components;
        sf::Vector2f position;
        float rotation;
        bool alive;  // Should be updated
        bool visible;  // Should be rendered
        bool for_deletion;  // Should be deleted
};

class Component {
    public:
        Component() = delete;
        bool is_for_deletion() const;
        virtual void update(const float& delta_time) = 0;
        virtual void render() = 0;
        virtual ~Component();
    protected:
        Entity* const parent;
        bool for_deletion;  // Should be removed
        explicit Component(Entity* const parent);
};