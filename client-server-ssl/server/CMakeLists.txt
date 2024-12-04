cmake_minimum_required(VERSION 3.10)
project(HttpServer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add Boost dependency
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

# HTTP Server
add_executable(http_server main.cpp)
target_link_libraries(http_server Boost::boost Boost::system OpenSSL::SSL OpenSSL::Crypto)