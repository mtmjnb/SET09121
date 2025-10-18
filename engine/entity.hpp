#pragma once
#include <memory>
#include <vector>
#include "ecm.hpp"

struct EntityManager {
    std::vector<std::shared_ptr<Entity>> list;
    void update(float delta_time);
    void render();
};