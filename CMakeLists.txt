cmake_minimum_required(VERSION 3.24)
project(project4)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio system REQUIRED)

add_executable(project4 main.cpp)
target_link_libraries(project4 sfml-graphics sfml-audio sfml-system)