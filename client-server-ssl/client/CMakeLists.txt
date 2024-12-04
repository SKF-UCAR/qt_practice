cmake_minimum_required(VERSION 3.10)
project(HttpClient)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add Boost dependency
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)

# HTTP Client
add_executable(http_client main.cpp)
target_link_libraries(http_client Boost::boost Boost::system OpenSSL::SSL OpenSSL::Crypto)