#ifndef PROYECTO_LL_PROGRAMACION_LL_IENTITY_H
#define PROYECTO_LL_PROGRAMACION_LL_IENTITY_H

#pragma once
#include <string>

class IEntity {
public:
    virtual ~IEntity() = default;

    [[nodiscard]] virtual std::string name() const noexcept = 0;

    [[nodiscard]] virtual std::string description() const noexcept = 0;
};

#endif //PROYECTO_LL_PROGRAMACION_LL_IENTITY_H
