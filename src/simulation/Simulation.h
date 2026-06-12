//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_SIMULATION_H
#define PROYECTO_LL_PROGRAMACION_LL_SIMULATION_H

#pragma once
#include "ISimulationObserver.h"
#include "../entities/Hero.h"
#include "../world/World.h"
#include <memory>
#include <string>
#include <vector>


class Simulation final {
public:
    Simulation(std::unique_ptr<Hero> hero, std::unique_ptr<World> world);

    void attachObserver(ISimulationObserver* observer);

    void detachObserver(ISimulationObserver* observer) noexcept;

    void run();

    [[nodiscard]] bool    heroWon()     const noexcept { return heroWon_;     }
    [[nodiscard]] int     turnsPlayed() const noexcept { return turnsPlayed_; }
    [[nodiscard]] Hero*   hero()        const noexcept { return hero_.get();  }

private:
    std::unique_ptr<Hero>  hero_;
    std::unique_ptr<World> world_;
    Room*                  currentRoom_ {nullptr};
    bool                   heroWon_     {false};
    int                    turnsPlayed_ {0};

    std::vector<ISimulationObserver*> observers_;

    void notify(const std::string& message) noexcept;

    void enterRoom(Room* room);
    void resolveTraps();
    void resolveItems();
    void resolveCombat();
    void moveToNextRoom();

    bool fightRound(Enemy& enemy);

    [[nodiscard]] Room* chooseNextRoom() const noexcept;
};

#endif //PROYECTO_LL_PROGRAMACION_LL_SIMULATION_H
