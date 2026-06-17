#include "Simulation.h"
#include "../entities/EnemyTypes.h"
#include <algorithm>
#include <stdexcept>
#include <string>


Simulation::Simulation(std::unique_ptr<Hero> hero, std::unique_ptr<World> world)
    : hero_(std::move(hero)), world_(std::move(world))
{
    if (!hero_)  { throw std::invalid_argument("Simulation: hero cannot be null."); }
    if (!world_) { throw std::invalid_argument("Simulation: world cannot be null."); }
}

void Simulation::attachObserver(ISimulationObserver* observer) {
    if (!observer) {
        throw std::invalid_argument("Cannot attach a null observer.");
    }
    const bool already = std::any_of(observers_.begin(), observers_.end(), [observer](const ISimulationObserver* o){
        return o == observer;
    });
    if (already) {
        throw std::invalid_argument("Observer already attached.");
    }
    observers_.push_back(observer);
}

void Simulation::detachObserver(ISimulationObserver* observer) noexcept {
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}

void Simulation::notify(const std::string& message) noexcept {
    for (ISimulationObserver* obs : observers_) {
        if (obs) {
            try { obs->onEvent(message); }
            catch (...)
            {

            }
        }
    }
}

void Simulation::run() {
    currentRoom_ = world_->startRoom();
    notify("=== Dragon's Keep: Adventure begins ===");
    notify("Hero " + hero_->name() + " enters the dungeon. " + hero_->description());

    while (hero_->isAlive() && currentRoom_ != nullptr) {
        ++turnsPlayed_;
        enterRoom(currentRoom_);

        if (!hero_->isAlive()) { break; }

        resolveTraps();
        if (!hero_->isAlive()) { break; }

        resolveItems();
        resolveCombat();

        if (!hero_->isAlive()) { break; }

        if (currentRoom_->isBossRoom()) {
            heroWon_ = true;
            break;
        }

        moveToNextRoom();
    }

    if (heroWon_) {
        notify("=== VICTORY! " + hero_->name() + " has slain the Dragon! ===");
    } else {
        notify("=== DEFEAT. " + hero_->name() + " has fallen in the dungeon. ===");
    }

    notify("Turns played: " + std::to_string(turnsPlayed_));
    notify("Final hero state: " + hero_->description());
}

void Simulation::enterRoom(Room* room) {
    room->markVisited();
    std::string msg = "--- Entering room: [" + room->id() + "] " + room->name();
    if (room->isBossRoom()) { msg += " *** BOSS ROOM ***"; }
    notify(msg);
    notify("    " + room->description());
}

void Simulation::resolveTraps() {
    const auto traps = currentRoom_->activatedTraps();
    for (Trap* trap : traps) {
        if (!trap) { continue; }
        hero_->takeDamage(trap->damage());
        notify("TRAP triggered: " + trap->name() + " deals " + std::to_string(trap->damage()) + " damage to " + hero_->name() + ". HP remaining: " + std::to_string(hero_->health()));
        trap->trigger();
        if (!hero_->isAlive()) {
            notify(hero_->name() + " was killed by the trap!");
            return;
        }
    }
}

void Simulation::resolveItems() {
    for (Weapon* w : currentRoom_->availableWeapons()) {
        if (!w) { continue; }
        hero_->boostAttack(w->attackBonus());
        notify("WEAPON found: " + w->description() + ". " + hero_->name() + " attack is now " + std::to_string(hero_->attack()));
        w->collect();
    }

    for (Potion* p : currentRoom_->availablePotions()) {
        if (!p) { continue; }
        hero_->heal(p->healAmount());
        notify("POTION found: " + p->description() + ". " + hero_->name() + " HP is now " + std::to_string(hero_->health()));
        p->consume();
    }
}

void Simulation::resolveCombat() {
    const auto enemies = currentRoom_->liveEnemies();
    if (enemies.empty()) {
        notify("Room is clear of enemies.");
        return;
    }

    for (Enemy* enemy : enemies) {
        if (!enemy) { continue; }
        notify("COMBAT: " + hero_->name() + " vs " + enemy->name() + " [HP:" + std::to_string(enemy->health()) + "]");

        while (hero_->isAlive() && enemy->isAlive()) {
            if (fightRound(*enemy)) { break; }
        }

        if (!hero_->isAlive()) {
            notify(hero_->name() + " has been defeated by " + enemy->name() + "!");
            return;
        }

        notify(hero_->name() + " defeated " + enemy->name() + "! +" + std::to_string(enemy->xpReward()) + " XP, +" + std::to_string(enemy->goldReward()) + " Gold.");
        hero_->gainExperience(enemy->xpReward());
        hero_->collectGold(enemy->goldReward());
        notify("Hero state: " + hero_->description());
    }
}

bool Simulation::fightRound(Enemy& enemy) {
    const int heroDmg = hero_->attack();
    enemy.takeDamage(heroDmg);
    notify("  " + hero_->name() + " attacks " + enemy.name() + " for " + std::to_string(heroDmg) + " dmg. Enemy HP: " + std::to_string(enemy.health()));

    if (!enemy.isAlive()) { return true; }

    const int enemyDmg = enemy.attack();
    hero_->takeDamage(enemyDmg);
    notify("  " + enemy.name() + " attacks " + hero_->name() + " for " + std::to_string(enemyDmg) + " dmg. Hero HP: " + std::to_string(hero_->health()));

    return !enemy.isAlive();
}

Room* Simulation::chooseNextRoom() const noexcept {
    Room* candidates[] = {
        currentRoom_->north(),
        currentRoom_->east(),
        currentRoom_->south(),
        currentRoom_->west()
    };
    for (Room* r : candidates) {
        if (r && !r->isVisited()) { return r; }
    }
    for (Room* r : candidates) {
        if (r) { return r; }
    }
    return nullptr;
}

void Simulation::moveToNextRoom() {
    Room* next = chooseNextRoom();
    if (!next) {
        notify("No more rooms to explore. Adventure ends here.");
        return;
    }
    notify(hero_->name() + " moves to " + next->name() + ".\n");
    currentRoom_ = next;
}
