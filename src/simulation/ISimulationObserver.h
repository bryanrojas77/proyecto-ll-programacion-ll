//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_ISIMULATIONOBSERVER_H
#define PROYECTO_LL_PROGRAMACION_LL_ISIMULATIONOBSERVER_H

#pragma once
#include <string>

class ISimulationObserver {
public:
    virtual ~ISimulationObserver() = default;
    
    virtual void onEvent(const std::string& message) = 0;
};


#endif //PROYECTO_LL_PROGRAMACION_LL_ISIMULATIONOBSERVER_H
