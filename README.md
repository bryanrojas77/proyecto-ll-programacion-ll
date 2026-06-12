# proyecto-ll-programacion-ll
Segundo proyecto de programación ll
Dragon's Keep
Motor de Simulación de Aventuras y Mazmorras

Proyecto II — EIF204 Programación II — I Ciclo 2026

Universidad Nacional de Costa Rica

Descripción
Dragon's Keep es una simulación automática en consola donde un héroe explora una mazmorra medieval compuesta por salas conectadas. El héroe enfrenta enemigos, activa trampas, recoge armas y pociones, y avanza hasta derrotar al jefe final (un dragón) o morir en el intento.
Toda la información del mundo se carga desde archivos de texto en la carpeta data/. El programa genera una bitácora de eventos (output/log.txt) y un reporte final (output/report.txt).

Estructura del proyecto
proyecto-ll-programacion-ll/
├── CMakeLists.txt
├── README.md
├── data/
│   ├── hero.txt
│   ├── world.txt
│   ├── enemies.txt
│   └── items.txt
├── output/
│   ├── log.txt
│   └── report.txt
└── src/
├── main.cpp
├── entities/
│   ├── IEntity.h
│   ├── Character.h / .cpp
│   ├── Hero.h / .cpp
│   ├── Enemy.h / .cpp
│   └── EnemyTypes.h
├── items/
│   ├── Item.h
│   └── ItemTypes.h
├── world/
│   ├── Room.h / .cpp
│   ├── World.h / .cpp
│   └── WorldLoader.h / .cpp
├── simulation/
│   ├── ISimulationObserver.h
│   ├── EnemyFactory.h / .cpp
│   └── Simulation.h / .cpp
└── output/
├── EventLog.h / .cpp
└── ReportGenerator.h / .cpp

Compilación en CLion

Abrir el proyecto en CLion
CLion detecta el CMakeLists.txt automáticamente
Hacer clic en el botón Build (martillo)
Las carpetas data/ y output/ se copian automáticamente junto al ejecutable

Compilación con g++ directo
bashmkdir -p output
g++ -std=c++20 -Wall -Wextra -o DragonKeep \
src/main.cpp \
src/entities/Character.cpp \
src/entities/Hero.cpp \
src/entities/Enemy.cpp \
src/world/Room.cpp \
src/world/World.cpp \
src/world/WorldLoader.cpp \
src/simulation/EnemyFactory.cpp \
src/simulation/Simulation.cpp \
src/output/EventLog.cpp \
src/output/ReportGenerator.cpp \
-I src
./DragonKeep

Ejecución
Correr desde la raíz del proyecto donde están las carpetas data/ y output/. En CLion usar el botón verde de Play.

Formato de archivos de entrada
data/hero.txt
name=Aldric the Brave
health=120
attack=18
defense=5
data/world.txt
ROOM id|nombre|descripcion
CONNECT roomId|north=roomId|south=roomId|east=roomId|west=roomId
Agregar [BOSS] en la descripción de la sala del jefe.
data/enemies.txt
roomId|type|name
Tipos disponibles: goblin, skeleton, dragon
data/items.txt
roomId|type|name|value
Tipos disponibles: weapon (bonus ATK), potion (HP curado), trap (daño)

Archivos de salida
ArchivoContenidooutput/log.txtBitácora completa de todos los eventos de la simulaciónoutput/report.txtReporte final con estado del héroe y salas visitadas

Patrones de diseño aplicados
PatrónDóndeJustificaciónObserverSimulation → EventLogRegistrar eventos sin acoplar el motor a clases de salidaFactory MethodEnemyFactoryCrear enemigos desde string sin acoplar al loaderCompositeRoomAgrupar enemigos e ítems bajo la interfaz IEntity

Integrantes:
-Bryan Alejandro Rojas Barrantes
-José Pablo Cortés Badilla
-José Alberto Ramos Saravia