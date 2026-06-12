//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_ENEMYTYPES_H
#define PROYECTO_LL_PROGRAMACION_LL_ENEMYTYPES_H

#pragma once
#include "Enemy.h"
#include <string>

class Goblin final : public Enemy {
public:
    explicit Goblin(const std::string& name = "Goblin")
        : Enemy(name, 30, 8, 2, 20, 10) {}

    [[nodiscard]] std::string description() const noexcept override {
        return "A sneaky goblin [HP:" + std::to_string(health_) + "]";
    }
};

class Skeleton final : public Enemy {
public:
    explicit Skeleton(const std::string& name = "Skeleton")
        : Enemy(name, 55, 15, 5, 40, 25) {}

    [[nodiscard]] std::string description() const noexcept override {
        return "A rattling skeleton [HP:" + std::to_string(health_) + "]";
    }
};

class Dragon final : public Enemy {
public:
    explicit Dragon(const std::string& name = "Ancient Dragon")
        : Enemy(name, 200, 35, 15, 300, 500) {}

    [[nodiscard]] std::string description() const noexcept override {
        return "The fearsome dragon [HP:" + std::to_string(health_) + "]";
    }

    [[nodiscard]] bool isBoss() const noexcept override { return true; }
};

#endif //PROYECTO_LL_PROGRAMACION_LL_ENEMYTYPES_H
