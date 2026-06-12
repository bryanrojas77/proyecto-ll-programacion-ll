//
// Created by kathy on 12/6/2026.
//

#include "EnemyFactory.h"
#include "EnemyTypes.h"
#include <stdexcept>

std::unique_ptr<Enemy> EnemyFactory::create(const std::string& type,
                                             const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("EnemyFactory: name cannot be empty.");
    }
    if (type == "goblin")   { return std::make_unique<Goblin>(name);   }
    if (type == "skeleton") { return std::make_unique<Skeleton>(name); }
    if (type == "dragon")   { return std::make_unique<Dragon>(name);   }

    throw std::invalid_argument("EnemyFactory: unknown enemy type '" + type + "'.");
}
