//
// Created by kathy on 12/6/2026.
//

#include "Room.h"
#include <stdexcept>

Room::Room(const std::string& id, const std::string& name, const std::string& description)
    : id_(id), name_(name), description_(description)
{
    if (id_.empty()) {
        throw std::invalid_argument("Room id cannot be empty.");
    }
    if (name_.empty()) {
        throw std::invalid_argument("Room name cannot be empty.");
    }
}

void Room::addEnemy(std::unique_ptr<Enemy> enemy) {
    if (enemy) {
        enemies_.push_back(std::move(enemy));
    }
}

std::vector<Enemy*> Room::liveEnemies() const {
    std::vector<Enemy*> alive;
    for (const auto& e : enemies_) {
        if (e && e->isAlive()) {
            alive.push_back(e.get());
        }
    }
    return alive;
}

bool Room::hasLiveEnemies() const noexcept {
    for (const auto& e : enemies_) {
        if (e && e->isAlive()) { return true; }
    }
    return false;
}

void Room::addWeapon(std::unique_ptr<Weapon> weapon) {
    if (weapon) { weapons_.push_back(std::move(weapon)); }
}

void Room::addPotion(std::unique_ptr<Potion> potion) {
    if (potion) { potions_.push_back(std::move(potion)); }
}

void Room::addTrap(std::unique_ptr<Trap> trap) {
    if (trap) { traps_.push_back(std::move(trap)); }
}

std::vector<Weapon*> Room::availableWeapons() const {
    std::vector<Weapon*> result;
    for (const auto& w : weapons_) {
        if (w && !w->isUsed()) { result.push_back(w.get()); }
    }
    return result;
}

std::vector<Potion*> Room::availablePotions() const {
    std::vector<Potion*> result;
    for (const auto& p : potions_) {
        if (p && !p->isUsed()) { result.push_back(p.get()); }
    }
    return result;
}

std::vector<Trap*> Room::activatedTraps() const {
    std::vector<Trap*> result;
    for (const auto& t : traps_) {
        if (t && !t->isUsed()) { result.push_back(t.get()); }
    }
    return result;
}
