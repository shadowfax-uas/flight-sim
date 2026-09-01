cmake_minimum_required(VERSION 3.20)
project(flight-sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(flight-core 
    src/Drone.cpp
    src/Mission.cpp
    src/GPS.cpp
    src/IMU.cpp
    src/Radar.cpp
    src/SensorManager.cpp
    src/TelemetryRecorder.cpp
    src/TelemetryReplay.cpp
    src/FlightSession.cpp
    )

target_include_directories(flight-core PUBLIC include)

add_executable(flight-sim 
    src/sim_main.cpp
)

target_link_libraries(flight-sim PRIVATE flight-core)

add_executable(flight-replay 
    src/replay_main.cpp
)

target_link_libraries(flight-replay PRIVATE flight-core)