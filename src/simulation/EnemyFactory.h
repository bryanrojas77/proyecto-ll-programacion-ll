//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_ENEMYFACTORY_H
#define PROYECTO_LL_PROGRAMACION_LL_ENEMYFACTORY_H

#pragma once
#include "Enemy.h"
#include <memory>
#include <string>

class EnemyFactory final {
public:
    [[nodiscard]] static std::unique_ptr<Enemy> create(const std::string& type,
                                                        const std::string& name);
};

#endif //PROYECTO_LL_PROGRAMACION_LL_ENEMYFACTORY_H
