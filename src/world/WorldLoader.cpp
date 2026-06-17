#include "WorldLoader.h"
#include "../entities/EnemyTypes.h"
#include "../items/ItemTypes.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

std::string WorldLoader::trim(const std::string& s) {
    const auto start = std::find_if_not(s.begin(), s.end(), [](unsigned char c){ return std::isspace(c); });
    const auto end = std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c){ return std::isspace(c); }).base();
    return (start < end) ? std::string(start, end) : std::string{};
}

int WorldLoader::parsePositiveInt(const std::string& s, const std::string& context) {
    try {
        const int val = std::stoi(s);
        if (val <= 0) {
            throw FileFormatError("Expected positive integer in " + context +
                                  ", got: " + s);
        }
        return val;
    } catch (const std::invalid_argument&) {
        throw FileFormatError("Expected integer in " + context + ", got: " + s);
    } catch (const std::out_of_range&) {
        throw FileFormatError("Integer out of range in " + context + ": " + s);
    }
}

std::unique_ptr<World> WorldLoader::loadWorld(const std::string& dataDir) {
    auto world = std::make_unique<World>();
    loadRooms      (*world, dataDir + "/world.txt");
    loadConnections(*world, dataDir + "/world.txt");
    loadEnemies    (*world, dataDir + "/enemies.txt");
    loadItems      (*world, dataDir + "/items.txt");
    return world;
}

std::unique_ptr<Hero> WorldLoader::loadHero(const std::string& dataDir) {
    const std::string path = dataDir + "/hero.txt";
    std::ifstream file{path};
    if (!file.is_open()) {
        throw FileFormatError("Cannot open hero file: " + path);
    }

    std::string name;
    int health = 0;
    int attack = 0;
    int defense = 0;

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty() || line[0] == '#') { continue; }

        std::istringstream ss(line);
        std::string key, value;
        if (!std::getline(ss, key, '=') || !std::getline(ss, value)) {
            throw FileFormatError("hero.txt line " + std::to_string(lineNum) + ": expected key=value format.");
        }
        key = trim(key);
        value = trim(value);

        if (key == "name") { name = value; }
        else if (key == "health") { health  = parsePositiveInt(value, "hero.txt health"); }
        else if (key == "attack") { attack  = parsePositiveInt(value, "hero.txt attack"); }
        else if (key == "defense") {
            try { defense = std::stoi(value); }
            catch (...) { throw FileFormatError("Invalid defense in hero.txt."); }
        }
    }

    if (name.empty()) { throw FileFormatError("hero.txt: missing 'name' field."); }
    if (health  == 0) { throw FileFormatError("hero.txt: missing 'health' field."); }
    if (attack  == 0) { throw FileFormatError("hero.txt: missing 'attack' field."); }

    return std::make_unique<Hero>(name, health, attack, defense);
}

void WorldLoader::loadRooms(World& world, const std::string& filePath) {
    std::ifstream file{filePath};
    if (!file.is_open()) {
        throw FileFormatError("Cannot open world file: " + filePath);
    }

    std::string line;
    int lineNum = 0;
    bool foundBoss = false;

    while (std::getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty() || line[0] == '#') { continue; }

        std::istringstream ss(line);
        std::string token;
        ss >> token;

        if (token == "ROOM") {
            std::string rest;
            std::getline(ss, rest);
            rest = trim(rest);

            std::istringstream parts(rest);
            std::string id, name, description;
            if (!std::getline(parts, id, '|') ||
                !std::getline(parts, name, '|') ||
                !std::getline(parts, description)) {
                throw FileFormatError("world.txt line " + std::to_string(lineNum) + ": ROOM requires id|name|description.");
            }
            id = trim(id);
            name = trim(name);
            description = trim(description);

            auto room = std::make_unique<Room>(id, name, description);

            if (description.find("[BOSS]") != std::string::npos) {
                room->markBossRoom();
                foundBoss = true;
            }
            world.addRoom(std::move(room));
        }
    }

    if (world.roomCount() == 0) {
        throw FileFormatError("world.txt: no rooms defined.");
    }
    if (!foundBoss) {
        throw FileFormatError("world.txt: no boss room found. Mark one description with [BOSS].");
    }
}

void WorldLoader::loadConnections(World& world, const std::string& filePath) {
    std::ifstream file{filePath};
    if (!file.is_open()) {
        throw FileFormatError("Cannot open world file: " + filePath);
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty() || line[0] == '#') { continue; }

        std::istringstream ss(line);
        std::string token;
        ss >> token;
        if (token != "CONNECT") { continue; }

        std::string rest;
        std::getline(ss, rest);
        rest = trim(rest);

        std::istringstream parts(rest);
        std::string segment;
        std::vector<std::string> segments;
        while (std::getline(parts, segment, '|')) {
            segments.push_back(trim(segment));
        }

        if (segments.empty()) {
            throw FileFormatError("world.txt line " + std::to_string(lineNum) + ": CONNECT has no data.");
        }

        const std::string sourceId = segments[0];
        Room* source = world.findRoom(sourceId);
        if (!source) {
            throw FileFormatError("world.txt line " + std::to_string(lineNum) + ": unknown room id '" + sourceId + "'.");
        }

        for (std::size_t i = 1; i < segments.size(); ++i) {
            std::istringstream kv(segments[i]);
            std::string dir, targetId;
            if (!std::getline(kv, dir, '=') || !std::getline(kv, targetId)) { continue; }
            dir = trim(dir);
            targetId = trim(targetId);
            Room* target = world.findRoom(targetId);
            if (!target) {
                throw FileFormatError("world.txt line " + std::to_string(lineNum) + ": unknown target room '" + targetId + "'.");
            }
            if (dir == "north") { source->setNorth(target); }
            else if (dir == "south") { source->setSouth(target); }
            else if (dir == "east") { source->setEast(target);  }
            else if (dir == "west") { source->setWest(target);  }
            else {
                throw FileFormatError("world.txt line " + std::to_string(lineNum) + ": unknown direction '" + dir + "'.");
            }
        }
    }
}

void WorldLoader::loadEnemies(World& world, const std::string& filePath) {
    std::ifstream file{filePath};
    if (!file.is_open()) {
        throw FileFormatError("Cannot open enemies file: " + filePath);
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty() || line[0] == '#') { continue; }

        std::istringstream parts(line);
        std::string roomId, type, name;
        if (!std::getline(parts, roomId, '|') || !std::getline(parts, type, '|') || !std::getline(parts, name)) {
            throw FileFormatError("enemies.txt line " + std::to_string(lineNum) + ": expected roomId|type|name.");
        }
        roomId = trim(roomId);
        type = trim(type);
        name = trim(name);

        Room* room = world.findRoom(roomId);
        if (!room) {
            throw FileFormatError("enemies.txt line " + std::to_string(lineNum) + ": unknown room id '" + roomId + "'.");
        }

        std::unique_ptr<Enemy> enemy;
        if (type == "goblin") { enemy = std::make_unique<Goblin>(name); }
        else if (type == "skeleton") { enemy = std::make_unique<Skeleton>(name); }
        else if (type == "dragon") { enemy = std::make_unique<Dragon>(name); }
        else {
            throw FileFormatError("enemies.txt line " + std::to_string(lineNum) + ": unknown enemy type '" + type + "'.");
        }
        room->addEnemy(std::move(enemy));
    }
}

void WorldLoader::loadItems(World& world, const std::string& filePath) {
    std::ifstream file{filePath};
    if (!file.is_open()) {
        throw FileFormatError("Cannot open items file: " + filePath);
    }

    std::string line;
    int lineNum = 0;
    while (std::getline(file, line)) {
        ++lineNum;
        line = trim(line);
        if (line.empty() || line[0] == '#') { continue; }

        std::istringstream parts(line);
        std::string roomId, type, name, valueStr;
        if (!std::getline(parts, roomId, '|') || !std::getline(parts, type, '|') || !std::getline(parts, name, '|') || !std::getline(parts, valueStr)) {
            throw FileFormatError("items.txt line " + std::to_string(lineNum) + ": expected roomId|type|name|value.");
        }
        roomId = trim(roomId);
        type = trim(type);
        name = trim(name);
        valueStr = trim(valueStr);

        Room* room = world.findRoom(roomId);
        if (!room) {
            throw FileFormatError("items.txt line " + std::to_string(lineNum) + ": unknown room id '" + roomId + "'.");
        }

        const int value = parsePositiveInt(valueStr, "items.txt line " + std::to_string(lineNum));

        if (type == "weapon") { room->addWeapon(std::make_unique<Weapon>(name, value)); }
        else if (type == "potion") { room->addPotion(std::make_unique<Potion>(name, value)); }
        else if (type == "trap") { room->addTrap  (std::make_unique<Trap>  (name, value)); }
        else {
            throw FileFormatError("items.txt line " + std::to_string(lineNum) + ": unknown item type '" + type + "'.");
        }
    }
}
