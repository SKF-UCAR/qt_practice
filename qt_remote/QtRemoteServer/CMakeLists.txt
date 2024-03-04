cmake_minimum_required(VERSION 3.11)

project(QtRemoteServer 
    VERSION 0.1
    LANGUAGES CXX)

define_project(${PROJECT_NAME}
    SOURCES
        QtRemoteServer.cpp
        RndGenerator.cpp
    HEADERS
        include/RndGenerator.hpp
    INTERFACE
        QtRemoteServer.hpp
    TESTS
        QtRemoteServer_test.cpp
    EXE_SOURCES
        main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${logx_SOURCE_DIR})

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