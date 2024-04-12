cmake_minimum_required(VERSION 3.11)

project(QtRemoteDemo2)

set(CMAKE_C_COMPILER_NAMES gcc clang icc cc)
set(CMAKE_CXX_COMPILER_NAMES g++ clang++ icpc c++ cxx)


set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/lib)


include(CheckCXXCompilerFlag)

macro(define_project _project_name)
    # Parse content of the SOURCES argument into list _APAR_DEFINE_PROJECT_SOURCES,
    # and do similar for arguments HEADERS, INTERFACE, etc.
    cmake_parse_arguments(
            _APAR_DEFINE_PROJECT
            ""
            ""
            "SOURCES;HEADERS;INTERFACE;TESTS;EXE_SOURCES"
            ${ARGN}
    )

    message("==> calling _apar_define_project (${_project_name} ...)")

    set(${_project_name}_HEADER_FILES
            ${_APAR_DEFINE_PROJECT_HEADERS})

    set(${_project_name}_SOURCE_FILES
            ${_APAR_DEFINE_PROJECT_SOURCES})

    set(${_project_name}_INTERFACE_FILES
            ${_APAR_DEFINE_PROJECT_INTERFACE})

    list(LENGTH ${_project_name}_INTERFACE_FILES NUMBER_OF_INTERFACE_FILES)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include AND NUMBER_OF_INTERFACE_FILES GREATER 0)
            list(TRANSFORM ${_project_name}_INTERFACE_FILES PREPEND "include/")
            list(APPEND ${_project_name}_HEADER_FILES ${${_project_name}_INTERFACE_FILES})    
    endif ()

    set(${_project_name}_TEST_FILES
            ${_APAR_DEFINE_PROJECT_TESTS})

    add_library(${_project_name} ${${_project_name}_SOURCE_FILES} ${${_project_name}_HEADER_FILES})
    add_library(APAR::${_project_name} ALIAS ${_project_name})

    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include AND NUMBER_OF_INTERFACE_FILES GREATER 0)
        message("==> adding interfaces " ${CMAKE_CURRENT_SOURCE_DIR}/include)
        target_include_directories(${_project_name}
                   PUBLIC
                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                   )
    endif ()

    list(LENGTH ${_project_name}_TEST_FILES NUMBER_OF_TEST_FILES)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test AND NUMBER_OF_TEST_FILES GREATER 0)
            message("==> adding tests " ${_project_name}_TEST)
            list(TRANSFORM ${_project_name}_TEST_FILES PREPEND "test/")
            add_executable(${_project_name}_TEST ${${_project_name}_TEST_FILES})
            if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_BUILD_TYPE MATCHES "Debug")
                target_compile_options(${_project_name}_TEST PRIVATE -fstandalone-debug)
            endif()
            target_include_directories(${_project_name}_TEST PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
            target_link_libraries(${_project_name}_TEST PUBLIC gtest gtest_main gcov ${_project_name})

            gtest_discover_tests(${_project_name}_TEST WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    endif ()

    set(${_project_name}_EXECUTABLE_FILES
        ${_APAR_DEFINE_PROJECT_EXE_SOURCES})
    list(LENGTH ${_project_name}_EXECUTABLE_FILES NUMBER_OF_EXECUTABLE_FILES)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/exe AND NUMBER_OF_EXECUTABLE_FILES GREATER 0)
        message("==> adding executables " ${CMAKE_CURRENT_SOURCE_DIR}/exe)

        list(TRANSFORM ${_project_name}_EXECUTABLE_FILES PREPEND "exe/")
        add_executable(${_project_name}_EXE ${${_project_name}_EXECUTABLE_FILES})

        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_BUILD_TYPE MATCHES "Debug")
            message("==>Clang Debug")
            target_compile_options(${_project_name}_EXE PRIVATE -fstandalone-debug)
        elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU" AND CMAKE_BUILD_TYPE MATCHES "Debug")
            message("==>GNU Debug")
            add_compile_options(-g -O0 -fprofile-arcs -ftest-coverage)
            target_link_libraries(${_project_name}_EXE PUBLIC gtest gtest_main gcov ${_project_name})
        endif()
        target_include_directories(${_project_name}_EXE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
        target_link_libraries(${_project_name}_EXE PUBLIC ${_project_name})
        set_target_properties(${_project_name}_EXE PROPERTIES OUTPUT_NAME "${_project_name}")
    endif ()

#     include(GNUInstallDirs)
#     set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${_project_name})
#
#     install(TARGETS ${_project_name}
#             EXPORT ${_project_name}-targets
#             LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#             ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#             RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# #            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#     )
#
#     set_target_properties(${_project_name} PROPERTIES EXPORT_NAME ${_project_name})
    
    # message( "CMAKE_CXX_COMPILER_ID=" ${CMAKE_CXX_COMPILER_ID})
    
    if( CMAKE_CXX_COMPILER_ID MATCHES "(C|c)lang" )
        target_compile_options(${_project_name} PUBLIC $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:-fprofile-instr-generate -fcoverage-mapping >)
    else ()
        target_compile_options(${_project_name} PUBLIC $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>: --coverage >)
    endif ()

    check_cxx_compiler_flag("-Wreorder" SUPPORTS_WREORDER)

    target_compile_options(${_project_name} PUBLIC $<$<BOOL:SUPPORTS_WREORDER>:-Wreorder>)

    # if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    #     install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    # endif()
    #
    # install(EXPORT ${_project_name}-targets
    #   FILE
    #     ${_project_name}Targets.cmake
    #   NAMESPACE
    #     APAR::
    #   DESTINATION
    #     ${INSTALL_CONFIGDIR}
    # )

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/${_project_name}ConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )

    # #Install the config, configversion and custom find modules
    # install(FILES
    # #    ${CMAKE_CURRENT_BINARY_DIR}/${_project_name}Config.cmake
    #     ${CMAKE_CURRENT_BINARY_DIR}/${_project_name}ConfigVersion.cmake
    #     DESTINATION ${INSTALL_CONFIGDIR}
    # )
    #
    # ##############################################
    # ## Exporting from the build tree
    # export(EXPORT ${_project_name}-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/${_project_name}Targets.cmake NAMESPACE APAR::)
    #
    # #Register package in user's package registry
    # export(PACKAGE ${_project_name})
endmacro()



# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Locate Qt
find_package(Qt6 REQUIRED COMPONENTS Core Network RemoteObjects SerialPort Widgets PATHS /usr NO_DEFAULT_PATH)


include(FetchContent)

FetchContent_Declare(
    logx
    GIT_REPOSITORY https://github.com/NCAR/logx
)

FetchContent_MakeAvailable(logx)
# include_directories(${logx_SOURCE_DIR})
# message("===> " ${logx_SOURCE_DIR})

include(CheckCXXCompilerFlag)


if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("======== DEBUG1 ========")
endif()

add_subdirectory(QtRemoteClient)
add_subdirectory(QtRemoteServer)

