//
// Created by kathy on 12/6/2026.
//

#include "World.h"

void World::addRoom(std::unique_ptr<Room> room) {
    if (!room) {
        throw std::invalid_argument("Cannot add a null room to the world.");
    }
    if (findRoom(room->id()) != nullptr) {
        throw std::invalid_argument("Duplicate room id: " + room->id());
    }
    rooms_.push_back(std::move(room));
}

Room* World::findRoom(const std::string& id) const noexcept {
    for (const auto& r : rooms_) {
        if (r && r->id() == id) { return r.get(); }
    }
    return nullptr;
}

Room* World::startRoom() const {
    if (rooms_.empty()) {
        throw std::runtime_error("The world has no rooms defined.");
    }
    return rooms_.front().get();
}
