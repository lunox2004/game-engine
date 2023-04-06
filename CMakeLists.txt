cmake_minimum_required(VERSION 3.0.0)
project(game_engine VERSION 0.1.0)
SET(SFML_STATIC_LIBRARIES TRUE)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR/bin})
SET(SFML_DIR ${CMAKE_SOURCE_DIR}/lib/cmake/SFML)
find_package(SFML COMPONENTS graphics system window REQUIRED)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
