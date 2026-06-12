//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_ENEMY_H
#define PROYECTO_LL_PROGRAMACION_LL_ENEMY_H

#pragma once
#include "Character.h"
#include <string>

class Enemy : public Character {
public:
    Enemy(const std::string& name, int health, int attack,
          int defense, int xpReward, int goldReward);

    virtual ~Enemy() = default;

    [[nodiscard]] int xpReward()   const noexcept { return xpReward_; }
    [[nodiscard]] int goldReward() const noexcept { return goldReward_; }

    [[nodiscard]] virtual bool isBoss() const noexcept { return false; }

private:
    int xpReward_;
    int goldReward_;
};




#endif //PROYECTO_LL_PROGRAMACION_LL_ENEMY_H
