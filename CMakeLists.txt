cmake_minimum_required(VERSION 3.20)
project(flight-sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

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
    src/FlightRecorder.cpp
    src/SimulatedDroneSource.cpp
    src/TelemetrySource.cpp
    src/MockTelemetrySource.cpp
    )

target_include_directories(flight-core PUBLIC include)

target_link_libraries(flight-core PUBLIC Threads::Threads)

add_executable(flight-sim 
    src/sim_main.cpp
)

target_link_libraries(flight-sim PRIVATE flight-core)

add_executable(flight-replay 
    src/replay_main.cpp
)

target_link_libraries(flight-replay PRIVATE flight-core)

add_executable(flight-stream-demo
    src/stream_main.cpp
)

target_link_libraries(flight-stream-demo PRIVATE flight-core)
