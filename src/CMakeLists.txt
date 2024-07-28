# Add all source files in this directory to the executable
file(GLOB_RECURSE SRC_FILES "*.cpp")

# Set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add files to the executable
set(CPP_SOURCE_FILES ${SRC_FILES})
