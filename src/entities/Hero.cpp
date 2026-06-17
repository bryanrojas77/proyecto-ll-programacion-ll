#include "Hero.h"
#include <string>

Hero::Hero(const std::string& name, int health, int attack, int defense)
    : Character(name, health, attack, defense) {}

std::string Hero::description() const noexcept {
    return "Hero [HP:" + std::to_string(health_) + "/" + std::to_string(maxHealth_) +
           " ATK:" + std::to_string(attack_) +
           " DEF:" + std::to_string(defense_) +
           " LVL:" + std::to_string(level_) +
           " XP:"  + std::to_string(experience_) +
           " GOLD:" + std::to_string(gold_) + "]";
}

void Hero::gainExperience(int amount) noexcept {
    if (amount <= 0) { return; }
    experience_ += amount;
    while (experience_ >= level_ * 100) {
        experience_ -= level_ * 100;
        levelUp();
    }
}

void Hero::collectGold(int amount) noexcept {
    if (amount > 0) { gold_ += amount; }
}

void Hero::levelUp() noexcept {
    ++level_;
    maxHealth_ += 20;
    health_    += 20;
    attack_    += 5;
    defense_   += 2;
}
