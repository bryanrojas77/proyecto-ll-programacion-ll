#ifndef PROYECTO_LL_PROGRAMACION_LL_HERO_H
#define PROYECTO_LL_PROGRAMACION_LL_HERO_H

#pragma once
#include "Character.h"
#include <string>

class Hero final : public Character {
public:
    Hero(const std::string& name, int health, int attack, int defense);

    [[nodiscard]] std::string description() const noexcept override;

    [[nodiscard]] int experience() const noexcept { return experience_; }
    [[nodiscard]] int level() const noexcept { return level_; }
    [[nodiscard]] int gold() const noexcept { return gold_; }

    void gainExperience(int amount) noexcept;

    void collectGold(int amount) noexcept;

private:
    int experience_ {0};
    int level_ {1};
    int gold_ {0};

    void levelUp() noexcept;
};


#endif //PROYECTO_LL_PROGRAMACION_LL_HERO_H
