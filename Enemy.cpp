//
// Created by kathy on 12/6/2026.
//

#include "Enemy.h"
#include <stdexcept>

Enemy::Enemy(const std::string& name, int health, int attack,
             int defense, int xpReward, int goldReward)
    : Character(name, health, attack, defense),
      xpReward_(xpReward), goldReward_(goldReward)
{
    if (xpReward_ <= 0) {
        throw std::invalid_argument("Enemy XP reward must be positive.");
    }
    if (goldReward_ < 0) {
        throw std::invalid_argument("Enemy gold reward must be non-negative.");
    }
}
