#ifndef PROYECTO_LL_PROGRAMACION_LL_REPORTGENERATOR_H
#define PROYECTO_LL_PROGRAMACION_LL_REPORTGENERATOR_H

#pragma once
#include "../simulation/Simulation.h"
#include "../world/World.h"
#include <string>

class ReportGenerator final {
public:
    explicit ReportGenerator(const std::string& outputPath);

    void generate(const Simulation& simulation, const World& world) const;

private:
    std::string outputPath_;
};


#endif //PROYECTO_LL_PROGRAMACION_LL_REPORTGENERATOR_H
