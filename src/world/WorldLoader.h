#ifndef PROYECTO_LL_PROGRAMACION_LL_WORLDLOADER_H
#define PROYECTO_LL_PROGRAMACION_LL_WORLDLOADER_H

#pragma once
#include "World.h"
#include "../entities/Hero.h"
#include <memory>
#include <string>
#include <stdexcept>

class FileFormatError : public std::runtime_error {
public:
    explicit FileFormatError(const std::string& message)
        : std::runtime_error(message) {}
};

class WorldLoader final {
public:
    [[nodiscard]] static std::unique_ptr<World> loadWorld(const std::string& dataDir);

    [[nodiscard]] static std::unique_ptr<Hero> loadHero(const std::string& dataDir);

private:
    static void loadRooms (World& world, const std::string& filePath);
    static void loadConnections (World& world, const std::string& filePath);
    static void loadEnemies (World& world, const std::string& filePath);
    static void loadItems (World& world, const std::string& filePath);

    [[nodiscard]] static std::string trim(const std::string& s);
    [[nodiscard]] static int parsePositiveInt(const std::string& s, const std::string& context);
};


#endif //PROYECTO_LL_PROGRAMACION_LL_WORLDLOADER_H
