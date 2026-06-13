//
// Created by kathy on 12/6/2026.
//

#include "ReportGenerator.h"
#include <fstream>
#include <stdexcept>
#include <string>

ReportGenerator::ReportGenerator(const std::string& outputPath)
    : outputPath_(outputPath)
{
    if (outputPath_.empty()) {
        throw std::invalid_argument("ReportGenerator: output path cannot be empty.");
    }
}

void ReportGenerator::generate(const Simulation& simulation, const World& world) const {
    std::ofstream file{outputPath_};
    if (!file.is_open()) {
        throw std::runtime_error("ReportGenerator: cannot open file: " + outputPath_);
    }

    file << "========================================\n";
    file << "   DRAGON'S KEEP - ADVENTURE REPORT\n";
    file << "========================================\n\n";

    file << "RESULT: " << (simulation.heroWon() ? "VICTORY" : "DEFEAT") << "\n";
    file << "Turns played: " << simulation.turnsPlayed() << "\n\n";

    const Hero* hero = simulation.hero();
    if (hero) {
        file << "--- HERO FINAL STATE ---\n";
        file << "Name   : " << hero->name()      << "\n";
        file << "Level  : " << hero->level()     << "\n";
        file << "HP     : " << hero->health()    << " / " << hero->maxHealth() << "\n";
        file << "Attack : " << hero->attack()    << "\n";
        file << "Defense: " << hero->defense()   << "\n";
        file << "XP     : " << hero->experience()<< "\n";
        file << "Gold   : " << hero->gold()      << "\n\n";
    }

    file << "--- ROOMS EXPLORED ---\n";
    int visited = 0;
    for (const auto& room : world.rooms()) {
        if (room && room->isVisited()) {
            ++visited;
            file << "  [" << room->id() << "] " << room->name();
            if (room->isBossRoom()) { file << " (Boss Room)"; }
            file << "\n";
        }
    }
    file << "Total rooms visited: " << visited << " / " << world.roomCount() << "\n\n";
    file << "========================================\n";
    file << "  End of report.\n";
    file << "========================================\n";
}
