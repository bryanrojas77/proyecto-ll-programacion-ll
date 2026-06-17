#ifndef PROYECTO_LL_PROGRAMACION_LL_ITEMTYPES_H
#define PROYECTO_LL_PROGRAMACION_LL_ITEMTYPES_H

#pragma once
#include "Item.h"
#include <stdexcept>
#include <string>

class Weapon final : public Item {
public:
    Weapon(const std::string& name, int attackBonus)
        : name_(name), attackBonus_(attackBonus)
    {
        if (name_.empty()) {
            throw std::invalid_argument("Weapon name cannot be empty.");
        }
        if (attackBonus_ <= 0) {
            throw std::invalid_argument("Weapon attack bonus must be positive.");
        }
    }

    [[nodiscard]] std::string name() const noexcept override { return name_; }
    [[nodiscard]] std::string description() const noexcept override {
        return "Weapon: " + name_ + " (+" + std::to_string(attackBonus_) + " ATK)";
    }
    [[nodiscard]] int attackBonus() const noexcept { return attackBonus_; }

    void collect() noexcept { used_ = true; }

private:
    std::string name_;
    int attackBonus_;
};

class Potion final : public Item {
public:
    Potion(const std::string& name, int healAmount)
        : name_(name), healAmount_(healAmount)
    {
        if (name_.empty()) {
            throw std::invalid_argument("Potion name cannot be empty.");
        }
        if (healAmount_ <= 0) {
            throw std::invalid_argument("Potion heal amount must be positive.");
        }
    }

    [[nodiscard]] std::string name() const noexcept override { return name_; }
    [[nodiscard]] std::string description() const noexcept override { return "Potion: " + name_ + " (+" + std::to_string(healAmount_) + " HP)"; }
    [[nodiscard]] int healAmount() const noexcept { return healAmount_; }

    void consume() noexcept { used_ = true; }

private:
    std::string name_;
    int healAmount_;
};

class Trap final : public Item {
public:
    Trap(const std::string& name, int damage)
        : name_(name), damage_(damage)
    {
        if (name_.empty()) {
            throw std::invalid_argument("Trap name cannot be empty.");
        }
        if (damage_ <= 0) {
            throw std::invalid_argument("Trap damage must be positive.");
        }
    }

    [[nodiscard]] std::string name() const noexcept override { return name_; }
    [[nodiscard]] std::string description() const noexcept override {
        return "Trap: " + name_ + " (-" + std::to_string(damage_) + " HP)";
    }
    [[nodiscard]] int damage() const noexcept { return damage_; }

    void trigger() noexcept { used_ = true; }

private:
    std::string name_;
    int damage_;
};


#endif //PROYECTO_LL_PROGRAMACION_LL_ITEMTYPES_H
