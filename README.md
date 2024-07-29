# Particle Life Simulation

An engaging implementation of the Particle Life simulation using C++, SDL2, and Dear ImGui. Watch as particles interact and form complex patterns based on simple rules!

This project does not build in Windows for some, reason. It doesn't contain any OS dependent code that would make it unable to work with Windows. I recommend installing Linux to work with this project as I find that to be easier that coding in Windows.

## Prerequisites

Before you begin, ensure you have the following installed:

- C++ compiler (GCC, Clang, or MSVC)
- CMake (version 3.10 or higher)
- SDL2 library (Optional SDL2 is included, confirmed working on Linux only. Should work with other OS too)
- Git (optional, for cloning the repository)

## Building the Project

Before building make sure you have the prerequisites downloaded.

#### Clone the repository:
If you have SDL2 installed in your system you can drop the `--recursive` flag.
```bash
git clone --recursive https://github.com/AnkushRoy-code/Particle.git
```

If you accidentally clone the repo without using `--recursive`, or you downloaded the repo using the GUI you can do this to fetch the depencency(SDL2) if you don't have them in your system:
```bash
git submodule update --init --recursive
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
If you have installed SDL2 in your system you can add `-DParticleVendored=OFF` flag to the command to save a ton of your time. Else you can just do this:
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
