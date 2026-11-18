# flight-sim

An educational C++20 project for building an unmanned aircraft system (UAS) flight simulator one piece at a time. It currently provides command-line demos for waypoint navigation, telemetry recording, and timed playback.

- `flight-sim` arms a drone, takes off, follows three predefined waypoints, and lands. It models position, altitude, battery consumption, and the `Grounded`, `Armed`, and `Flying` states, with simple GPS, IMU, and radar readouts.
- `flight-stream-demo` publishes seven mock telemetry samples from a background thread, 500 ms apart, while the main thread remains active.
- `flight-replay` loads a CSV log, reports duration, horizontal distance traveled, maximum altitude, and battery consumption, then prints records according to their timestamps.

Build with CMake 3.20+ and a C++20 compiler and standard library supporting `std::format` and `std::jthread`. CMake detects platform thread support; no third-party libraries are required. From the repository root:

```sh
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

Run the demos and replay a checked-in sample log:

```sh
./build/flight-sim
./build/flight-stream-demo
./build/flight-replay logs/flight_1793193308.csv 2.0
```

Replay accepts `flight-replay <telemetry_file> [playback_speed]`. Speed defaults to `1.0`; use `2.0` for twice normal speed or `0.5` for half speed. It must be positive and finite.

The demos create `logs/flight_<epoch-seconds>.csv` and `logs/stream_<epoch-seconds>.csv` relative to the working directory. Pass either generated file to `flight-replay`. Each CSV uses this exact header:

```csv
frame,elapsedTimeSeconds,x,y,altitude,battery,state
```

Elapsed time is in seconds, battery is a percentage, and spatial values use unspecified simulation units. Replay rejects malformed rows, non-finite numbers, invalid states, battery values outside 0–100, and negative or decreasing timestamps; equal timestamps are allowed.

The shared `flight-core` library connects telemetry sources to `FlightRecorder`, which assigns frame numbers, stores records in a `FlightSession`, and writes CSV through `TelemetryRecorder`. Headers live in `include/`, implementations and executable entry points in `src/`, and tests and CSV fixtures in `tests/`. Tests cover replay validation and seeking, failed reloads, statistics, and playback callback order. Example logs are in `logs/`.

To change the demo mission, edit the waypoints in [src/sim_main.cpp](src/sim_main.cpp); movement and battery behavior live in [src/Drone.cpp](src/Drone.cpp). Movement advances simulated time without real-time delays, and sensor readings derive directly from drone state. UDP telemetry is unfinished and excluded from the build; live MAVLink ingestion is not implemented.
