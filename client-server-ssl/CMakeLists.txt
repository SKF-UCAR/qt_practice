cmake_minimum_required(VERSION 3.10)
project(HTTPServerClient)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")

# set output folders broEXE and libs to be easely reachable
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/lib)

# Add Boost dependency
find_package(Boost REQUIRED COMPONENTS system)

# add sub-projects
add_subdirectory (client)
add_subdirectory (server)
