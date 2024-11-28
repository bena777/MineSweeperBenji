cmake_minimum_required(VERSION 3.24)
project(project4)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.6.2 COMPONENTS graphics audio system REQUIRED)
add_executable(project4 main.cpp
        minesweeper.cpp Button.cpp GameState.cpp Tile.cpp
        Toolbox.cpp)
target_link_libraries(project4 sfml-graphics sfml-audio sfml-system)
target_include_directories(project4 PRIVATE ${SFML_INCLUDE_DIR})
