cmake_minimum_required(VERSION 3.20)
project(flight-sim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

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

add_executable(flight-tests
    tests/replay_tests.cpp
)

target_link_libraries(flight-tests PRIVATE flight-core)

add_test(
    NAME replay-valid
    COMMAND flight-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/valid.csv
)

add_executable(flight-invalid-state-tests
    tests/invalid_state_tests.cpp
)

target_link_libraries(flight-invalid-state-tests PRIVATE flight-core)

add_test(
    NAME replay-invalid-number
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_number.csv
)

add_test(
    NAME replay-invalid-state
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_state.csv
)

add_test(
    NAME replay-partial-number
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/partial_number.csv
)

add_test(
    NAME replay-partial-x
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/partial_x.csv
)

add_test(
    NAME replay-negative-frame
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/negative_frame.csv
)

add_test(
    NAME replay-invalid-frame
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_frame.csv
)

add_test(
    NAME replay-invalid-header
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_header.csv
)

add_test(
    NAME replay-missing-column
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/missing_column.csv
)

add_test(
    NAME replay-extra-column
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/extra_column.csv
)

set_tests_properties(
    replay-missing-column
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: expected 7 columns, found 6"
)

set_tests_properties(
    replay-extra-column
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: expected 7 columns, found 8"
)

add_executable(flight-replay 
    src/replay_main.cpp
)

target_link_libraries(flight-replay PRIVATE flight-core)

add_executable(flight-stream-demo
    src/stream_main.cpp
)

target_link_libraries(flight-stream-demo PRIVATE flight-core)
