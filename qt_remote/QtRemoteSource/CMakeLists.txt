cmake_minimum_required(VERSION 3.11)

project(sub_project 
    VERSION 0.1
    LANGUAGES CXX)

define_project(${PROJECT_NAME}
    SOURCES
        example.cpp
    HEADERS
        include/internal.hpp
    INTERFACE
        example.hpp
    TESTS
        example_test.cpp
    EXE_SOURCES
        main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    logx
    Qt6::Core 
    Qt6::Network
    Qt6::RemoteObjects
    Qt6::SerialPort
    Qt6::Widgets     
)

#target_link_libraries(${PROJECT_NAME} <libs>)

install (TARGETS ${PROJECT_NAME} DESTINATION ${APAR_INSTALL_DIR}/bin )