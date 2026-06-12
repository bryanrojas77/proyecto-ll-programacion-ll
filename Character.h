//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_CHARACTER_H
#define PROYECTO_LL_PROGRAMACION_LL_CHARACTER_H


#pragma once
#include "IEntity.h"
#include <stdexcept>
#include <string>


class Character : public IEntity {
public:
    Character(const std::string& name, int health, int attack, int defense)
        : name_(name), health_(health), maxHealth_(health),
          attack_(attack), defense_(defense)
    {
        if (name_.empty()) {
            throw std::invalid_argument("Character name cannot be empty.");
        }
        if (health_ <= 0) {
            throw std::invalid_argument("Character health must be positive.");
        }
        if (attack_ <= 0) {
            throw std::invalid_argument("Character attack must be positive.");
        }
        if (defense_ < 0) {
            throw std::invalid_argument("Character defense must be non-negative.");
        }
    }

    virtual ~Character() = default;

    [[nodiscard]] std::string name() const noexcept override { return name_; }

    [[nodiscard]] int health()     const noexcept { return health_; }
    [[nodiscard]] int maxHealth()  const noexcept { return maxHealth_; }
    [[nodiscard]] int attack()     const noexcept { return attack_; }
    [[nodiscard]] int defense()    const noexcept { return defense_; }
    [[nodiscard]] bool isAlive()   const noexcept { return health_ > 0; }

    void takeDamage(int rawDamage) noexcept {
        const int effective = rawDamage - defense_;
        if (effective > 0) {
            health_ -= effective;
            if (health_ < 0) { health_ = 0; }
        }
    }

    void heal(int amount) noexcept {
        if (amount > 0) {
            health_ += amount;
            if (health_ > maxHealth_) { health_ = maxHealth_; }
        }
    }
    
    void boostAttack(int bonus) noexcept {
        if (bonus > 0) { attack_ += bonus; }
    }

protected:
    std::string name_;
    int health_;
    int maxHealth_;
    int attack_;
    int defense_;
};

#endif //PROYECTO_LL_PROGRAMACION_LL_CHARACTER_H
