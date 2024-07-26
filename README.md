# Particle Life Simulation

An engaging implementation of the Particle Life simulation using C++, SDL2, and Dear ImGui. Watch as particles interact and form complex patterns based on simple rules!

## Prerequisites

Before you begin, ensure you have the following installed:

- C++ compiler (GCC, Clang, or MSVC)
- CMake (version 3.10 or higher)
- SDL2 library (I tried my best to ship this by default in another branch Included-SDL2 but it doesn't work because of my lack of knowledge)
- Git (optional, for cloning the repository)

## Building the Project

Before building make sure you have the prerequisites downloaded.

Clone the repository:
```git clone https://github.com/AnkushRoy-code/Particle.git```
and then
```cd Particle```

Create a build directory and navigate to it:
```mkdir build && cd build```

Generate the build files:
```cmake ..```

Build the project:
```make```
And hope you don't get any errors.

## Running the Simulation
After building, you can run the simulation:

On Windows: ```.\particle.exe```
On macOS/Linux: ```./particle```
