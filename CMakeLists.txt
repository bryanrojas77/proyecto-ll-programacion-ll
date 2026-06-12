cmake_minimum_required(VERSION 4.2)
project(proyecto_ll_programacion_ll)

set(CMAKE_CXX_STANDARD 26)

add_executable(proyecto_ll_programacion_ll main.cpp
        Character.cpp
        Character.h
        Enemy.cpp
        Enemy.h
        EnemyTypes.h
        Hero.cpp
        Hero.h
        IEntity.h
        Item.h
        ItemTypes.h
        EventLog.cpp
        EventLog.h
        ReportGenerator.cpp
        ReportGenerator.h)
