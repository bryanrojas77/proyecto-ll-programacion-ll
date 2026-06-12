cmake_minimum_required(VERSION 3.20)
project(proyecto_ll_programacion_ll LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
        src/main.cpp
        src/entities/Character.cpp
        src/entities/Hero.cpp
        src/entities/Enemy.cpp
        src/world/Room.cpp
        src/world/World.cpp
        src/world/WorldLoader.cpp
        src/simulation/EnemyFactory.cpp
        src/simulation/Simulation.cpp
        src/output/EventLog.cpp
        src/output/ReportGenerator.cpp
)

add_executable(proyecto_ll_programacion_ll ${SOURCES})

target_include_directories(proyecto_ll_programacion_ll PRIVATE src)

add_custom_command(TARGET proyecto_ll_programacion_ll POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:proyecto_ll_programacion_ll>/data
)

add_custom_command(TARGET proyecto_ll_programacion_ll POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:proyecto_ll_programacion_ll>/output
)