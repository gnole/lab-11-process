cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX)

set(
        HUNTER_CACHE_SERVERS
        "https://github.com/bmstu-iu8-cpp-sem-3/hunter-cache"
        CACHE STRING "Default cache server"
)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
        SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(template)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(BoostProcess)
find_package(BoostProcess CONFIG REQUIRED)

hunter_add_package(Boost COMPONENTS program_options
        thread
        log
        filesystem
        )
find_package(Boost CONFIG REQUIRED program_options
        thread
        log
        log_setup
        filesystem
        )

hunter_add_package(Async++)
find_package(Async++ CONFIG REQUIRED)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_executable(tests
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Parameters.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Builder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sources/Process.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
        )
target_include_directories(tests
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
target_link_libraries(tests
        Async++::Async++
        Boost::program_options
        Boost::thread
        Boost::log
        Boost::log_setup
        Boost::filesystem
        GTest::gmock_main
        )

install(TARGETS tests DESTINATION bin)
set(CPACK_PACKAGE_NAME "SimpleApp")
set(CPACK_PACKAGE_VENDOR "MyComp")
set(CPACK_VERBATIM_VARIABLES true)
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)
include(CPack)
enable_testing()
add_test(NAME unit_tests COMMAND tests)
