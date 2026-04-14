# Simple Cache Controller Simulator

<img width="443" height="408" alt="image" src="https://github.com/user-attachments/assets/fdffd701-2e86-4c5d-a27f-8f486c999163" />


## Description
This project provides a C++ simulation of a basic cache controller state machine. It simulates memory requests (read/write) and accurately models the behavior of an underlying cache system through distinct operational stages, including:
- **Idle**: Waiting for the next memory request.
- **Compare Tag**: Checking if the requested block is resident in the cache (identifying a hit or miss).
- **Allocate**: Fetching data from main memory into the cache upon encountering a read or write miss.
- **Write Back**: Evicting modified (dirty) cache lines cleanly back to main memory before allocating new data blocks.

The simulation utilizes randomized probability models to dictate memory readiness delays, cache hit/miss probabilities, and dirty bit states, creating a realistic textual demonstration of cache control interactions.

## Prerequisites
To compile and execute this simulator, you must have a C++ compiler installed on your system that supports the C++11 standard or later.
- GCC (`g++`)
- Clang (`clang++`)
- Microsoft Visual C++ (`MSVC`)

## Building and Compilation
To compile the source code, open your terminal, navigate to the directory containing `simpleCacheControllerSimulator.cpp`, and execute the following command:

```bash
g++ -std=c++11 -O2 -o cache_simulator simpleCacheControllerSimulator.cpp
```

## Usage
Run the compiled executable directly from your terminal:

```bash
./cache_simulator
```

Upon launching the program, an interactive prompt will appear:
```text
Enter the number of random requests you want to simulate: 
```
Provide a positive integer indicating how many completely randomized memory requests the simulator should generate and process.

## How It Works
1. **Request Generation**: The program creates `N` dynamic cache requests utilizing random weighted distributions:
   - **Request Type**: Read (20%) or Write (80%).
   - **Cache Miss**: Represents a 90% chance of missing the cache upon memory access.
   - **Dirty Bit State**: 80% likelihood for the an evicted cache block to already be dirty.
2. **State Machine Execution**: For each individual request, the system processes it chronologically through modeled finite-state machine transitions, simulating realistic behavior.
3. **Wait Cycles**: When main memory is unready or unresponsive, the simulation dynamically inserts wait cycles. Short artificial delays (`sleep_for`) graphically represent stall cycles on standard output via loading dots (`.`).

## Author
Developed by: **Saad Al Abeed** (ID: 230041142)
