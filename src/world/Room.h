//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_ROOM_H
#define PROYECTO_LL_PROGRAMACION_LL_ROOM_H

#pragma once
#include "../entities/Enemy.h"
#include "../items/ItemTypes.h"
#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class Room final {
public:
    Room(const std::string& id,
         const std::string& name,
         const std::string& description);

    [[nodiscard]] const std::string& id()          const noexcept { return id_; }
    [[nodiscard]] const std::string& name()        const noexcept { return name_; }
    [[nodiscard]] const std::string& description() const noexcept { return description_; }
    [[nodiscard]] bool isVisited()                 const noexcept { return visited_; }
    [[nodiscard]] bool isBossRoom()                const noexcept { return bossRoom_; }

    void markVisited()  noexcept { visited_  = true; }
    void markBossRoom() noexcept { bossRoom_ = true; }

    void setNorth(Room* room) noexcept { north_ = room; }
    void setSouth(Room* room) noexcept { south_ = room; }
    void setEast (Room* room) noexcept { east_  = room; }
    void setWest (Room* room) noexcept { west_  = room; }

    [[nodiscard]] Room* north() const noexcept { return north_; }
    [[nodiscard]] Room* south() const noexcept { return south_; }
    [[nodiscard]] Room* east()  const noexcept { return east_;  }
    [[nodiscard]] Room* west()  const noexcept { return west_;  }

    void addEnemy(std::unique_ptr<Enemy> enemy);
    [[nodiscard]] std::vector<Enemy*> liveEnemies() const;
    [[nodiscard]] bool hasLiveEnemies() const noexcept;

    void addWeapon(std::unique_ptr<Weapon> weapon);
    void addPotion(std::unique_ptr<Potion> potion);
    void addTrap  (std::unique_ptr<Trap>   trap);

    [[nodiscard]] std::vector<Weapon*> availableWeapons() const;
    [[nodiscard]] std::vector<Potion*> availablePotions() const;
    [[nodiscard]] std::vector<Trap*>   activatedTraps()   const;

private:
    std::string id_;
    std::string name_;
    std::string description_;
    bool visited_  {false};
    bool bossRoom_ {false};

    Room* north_ {nullptr};
    Room* south_ {nullptr};
    Room* east_  {nullptr};
    Room* west_  {nullptr};

    std::vector<std::unique_ptr<Enemy>>  enemies_;
    std::vector<std::unique_ptr<Weapon>> weapons_;
    std::vector<std::unique_ptr<Potion>> potions_;
    std::vector<std::unique_ptr<Trap>>   traps_;
};

#endif //PROYECTO_LL_PROGRAMACION_LL_ROOM_H
