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
    src/TelemetryStatistics.cpp
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

add_executable(replay-failed-reload
    tests/reload_tests.cpp
)

target_link_libraries(replay-failed-reload PRIVATE flight-core)

add_test(
    NAME replay-failed-reload
    COMMAND replay-failed-reload
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/valid.csv
)

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

set_tests_properties(
    replay-invalid-number
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid elapsedTimeSeconds value: banana"
)

add_test(
    NAME replay-invalid-state
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_state.csv
)

set_tests_properties(
    replay-invalid-state
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid state value: Potato"
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

set_tests_properties(
    replay-negative-frame
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid frame value: -1"
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

set_tests_properties(
    replay-missing-column
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: expected 7 columns, found 6"
)

add_test(
    NAME replay-extra-column
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/extra_column.csv
)

set_tests_properties(
    replay-extra-column
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: expected 7 columns, found 8"
)

add_test(
    NAME replay-invalid-battery
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_battery.csv
)

set_tests_properties(
    replay-invalid-battery
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid battery value: banana"
)

add_test(
    NAME replay-invalid-x
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_x.csv
)

set_tests_properties(
    replay-invalid-x
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid x value: banana"
)

add_test(
    NAME replay-invalid-y
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_y.csv
)

set_tests_properties(
    replay-invalid-y
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid y value: banana"
)

add_test(
    NAME replay-invalid-altitude
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_altitude.csv
)

set_tests_properties(
    replay-invalid-altitude
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: invalid altitude value: banana"
)

add_test(
    NAME replay-invalid-battery-range
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_battery_range.csv
)

set_tests_properties(
    replay-invalid-battery-range
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: battery out of range: 125"
)

add_test(
    NAME replay-negative-battery
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/negative_battery.csv
)

set_tests_properties(
    replay-negative-battery
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: battery out of range: -1"
)

add_test(
    NAME replay-invalid-nan
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_nan.csv
)

add_test(
    NAME replay-invalid-infinity
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/invalid_infinity.csv
)

add_test(
    NAME replay-negative-elapsed-time
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/negative_elapsed_time.csv
)

set_tests_properties(
    replay-negative-elapsed-time
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 2: elapsedTimeSeconds cannot be negative: -0.5"
)

add_test(
    NAME replay-backward-time
    COMMAND flight-invalid-state-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/backward_time.csv
)

set_tests_properties(
    replay-backward-time
    PROPERTIES
    PASS_REGULAR_EXPRESSION "Line 4: elapsedTimeSeconds moved backward: 0.5"
)

add_test(
    NAME replay-duplicate-time
    COMMAND flight-tests
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/data/duplicate_time.csv
)

add_executable(statistics-tests
    tests/statistics_tests.cpp
)

target_link_libraries(statistics-tests PRIVATE flight-core)

add_test(
    NAME statistics-tests
    COMMAND statistics-tests
)

add_executable(flight-replay 
    src/replay_main.cpp
)

target_link_libraries(flight-replay PRIVATE flight-core)

add_executable(flight-stream-demo
    src/stream_main.cpp
)

target_link_libraries(flight-stream-demo PRIVATE flight-core)
