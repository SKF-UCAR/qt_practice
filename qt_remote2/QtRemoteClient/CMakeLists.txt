cmake_minimum_required(VERSION 3.11)

project(QtRemoteClient 
    VERSION 0.1
    LANGUAGES CXX)

define_project(${PROJECT_NAME}
    SOURCES
        QtRemoteClient.cpp
    HEADERS
    INTERFACE
        QtRemoteClient.hpp
    TESTS
        QtRemoteClient_test.cpp
    EXE_SOURCES
        main.cpp
)

target_link_libraries(${PROJECT_NAME} 
    logx
    QtRemoteServer
    Qt6::Core 
    Qt6::Network
    Qt6::RemoteObjects
    Qt6::Widgets     
)

#target_link_libraries(${PROJECT_NAME} <libs>)

install (TARGETS ${PROJECT_NAME} DESTINATION ${APAR_INSTALL_DIR}/bin )