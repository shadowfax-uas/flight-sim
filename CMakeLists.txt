cmake_minimum_required(VERSION 3.20)
project(flight-sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(flight-sim 
    src/main.cpp
    src/Drone.cpp
    src/Mission.cpp
    src/GPS.cpp
    src/IMU.cpp
    src/Radar.cpp
    src/SensorManager.cpp
    src/TelemetryRecorder.cpp
    src/TelemetryReplay.cpp
    )

target_include_directories(flight-sim PRIVATE include)