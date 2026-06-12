cmake_minimum_required(VERSION 3.20)
project(DragonKeep LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# All source files
set(SOURCES
        src/main.cpp
        src/entities/Character.cpp
        src/entities/Hero.cpp
        src/entities/Enemy.cpp
        src/items/Item.h
        src/world/Room.cpp
        src/world/World.cpp
        src/world/WorldLoader.cpp
        src/simulation/EnemyFactory.cpp
        src/simulation/Simulation.cpp
        src/output/EventLog.cpp
        src/output/ReportGenerator.cpp
)

add_executable(DragonKeep ${SOURCES})

target_include_directories(DragonKeep PRIVATE src)

# Copy data folder next to the executable so relative paths work
add_custom_command(TARGET DragonKeep POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:DragonKeep>/data
)

# Create output directory next to executable
add_custom_command(TARGET DragonKeep POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:DragonKeep>/output
)