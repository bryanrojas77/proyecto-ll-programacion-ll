#ifndef PROYECTO_LL_PROGRAMACION_LL_ITEM_H
#define PROYECTO_LL_PROGRAMACION_LL_ITEM_H

#pragma once
#include "../entities/IEntity.h"

class Item : public IEntity {
public:
    virtual ~Item() = default;

    [[nodiscard]] bool isUsed() const noexcept { return used_; }

protected:
    bool used_ {false};
};

#endif //PROYECTO_LL_PROGRAMACION_LL_ITEM_H
