//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_WORLD_H
#define PROYECTO_LL_PROGRAMACION_LL_WORLD_H

#pragma once
#include "Room.h"
#include <memory>
#include <string>
#include <vector>

class World final {
public:
    void addRoom(std::unique_ptr<Room> room);

    [[nodiscard]] Room* findRoom(const std::string& id) const noexcept;

    [[nodiscard]] Room* startRoom() const;

    [[nodiscard]] const std::vector<std::unique_ptr<Room>>& rooms() const noexcept {
        return rooms_;
    }

    [[nodiscard]] std::size_t roomCount() const noexcept { return rooms_.size(); }

private:
    std::vector<std::unique_ptr<Room>> rooms_;
};

#endif //PROYECTO_LL_PROGRAMACION_LL_WORLD_H
