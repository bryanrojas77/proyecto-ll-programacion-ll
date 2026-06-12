#include <iostream>
#include "WorldLoader.h"
#include "Simulation.h"
#include "EventLog.h"
#include "ReportGenerator.h"
#include <stdexcept>

int main() {
    try {
        const std::string dataDir   = "data";
        const std::string outputDir = "output";

        auto world = WorldLoader::loadWorld(dataDir);
        auto hero  = WorldLoader::loadHero(dataDir);

        World* worldPtr = world.get();

        EventLog eventLog{outputDir + "/log.txt"};

        Simulation simulation{std::move(hero), std::move(world)};
        simulation.attachObserver(&eventLog);
        simulation.run();

        eventLog.flush();

        ReportGenerator report{outputDir + "/report.txt"};
        report.generate(simulation, *worldPtr);

        std::cout << "\nLog saved to:    " << outputDir << "/log.txt\n";
        std::cout << "Report saved to: " << outputDir << "/report.txt\n";

    } catch (const FileFormatError& e) {
        std::cerr << "[FILE ERROR] " << e.what() << "\n";
        return 2;
    } catch (const std::invalid_argument& e) {
        std::cerr << "[INVALID ARGUMENT] " << e.what() << "\n";
        return 3;
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << "\n";
        return 1;
    }

    return 0;
}
