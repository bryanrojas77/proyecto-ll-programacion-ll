//
// Created by kathy on 12/6/2026.
//

#include "EventLog.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

EventLog::EventLog(const std::string& outputPath)
    : outputPath_(outputPath)
{
    if (outputPath_.empty()) {
        throw std::invalid_argument("EventLog: output path cannot be empty.");
    }
}

void EventLog::onEvent(const std::string& message) {
    events_.push_back(message);
    std::cout << message << "\n";
}

void EventLog::flush() const {
    std::ofstream file{outputPath_};
    if (!file.is_open()) {
        throw std::runtime_error("EventLog: cannot open output file: " + outputPath_);
    }
    file << "=== Dragon's Keep - Event Log ===\n\n";
    for (const auto& event : events_) {
        file << event << "\n";
    }
    file << "\n=== Total events: " << events_.size() << " ===\n";
}
