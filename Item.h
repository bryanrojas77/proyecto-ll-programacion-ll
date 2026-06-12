//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_ITEM_H
#define PROYECTO_LL_PROGRAMACION_LL_ITEM_H

#pragma once
#include "IEntity.h"
#include <string>


class Item : public IEntity {
public:
    virtual ~Item() = default;

    [[nodiscard]] bool isUsed() const noexcept { return used_; }

protected:
    bool used_ {false};
};

#endif //PROYECTO_LL_PROGRAMACION_LL_ITEM_H
