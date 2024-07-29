# Particle Life Simulation

An engaging implementation of the Particle Life simulation using C++, SDL2, and Dear ImGui. Watch as particles interact and form complex patterns based on simple rules!

## Prerequisites

Before you begin, ensure you have the following installed:

- C++ compiler (GCC, Clang, or MSVC)
- CMake (version 3.10 or higher)
- SDL2 library (Optional SDL2 is included, confirmed working on Linux only. Should work with other OS too)
- Git (optional, for cloning the repository)

## Building the Project

Before building make sure you have the prerequisites downloaded.

#### Clone the repository:
```bash
git clone https://github.com/AnkushRoy-code/Particle.git
```
#### and then
```bash
cd Particle
```

#### Create a build directory and navigate to it:
```bash
mkdir build && cd build
```

#### Generate the build files:
If you have installed SDL2 in your system you can add ```-DParticleVendored=OFF``` flag to the command to save a ton of your time. Else you can just do this:
```bash 
cmake ..
``` 

#### Build the project:
```bash
make
```
And hope you don't get any errors.

## Running the Simulation
After building, you can run the simulation:

On Windows:
```bash
.\particle.exe
```
On macOS/Linux:
```bash
./particle
```
## Usage
For detailed usage instructions, refer to the [Usage Guide](./USAGE.md).
