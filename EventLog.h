//
// Created by kathy on 12/6/2026.
//

#ifndef PROYECTO_LL_PROGRAMACION_LL_EVENTLOG_H
#define PROYECTO_LL_PROGRAMACION_LL_EVENTLOG_H

#pragma once
#include "ISimulationObserver.h"
#include <string>
#include <vector>
#include <stdexcept>

class EventLog final : public ISimulationObserver {
public:

    explicit EventLog(const std::string& outputPath);

    void onEvent(const std::string& message) override;

    void flush() const;

    [[nodiscard]] std::size_t eventCount() const noexcept { return events_.size(); }

    [[nodiscard]] const std::vector<std::string>& events() const noexcept {
        return events_;
    }

private:
    std::string              outputPath_;
    std::vector<std::string> events_;
};

#endif //PROYECTO_LL_PROGRAMACION_LL_EVENTLOG_H
