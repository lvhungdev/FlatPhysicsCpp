cmake_minimum_required(VERSION 3.26)
project(FlatPhysics)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories(.)

file(GLOB SourceFiles Renderer/*.cpp Physics/*.cpp Physics/Core/*.cpp Physics/Collision/*.cpp Physics/Utils/*.cpp)
file(GLOB HeaderFiles Renderer/*.h Physics/*.h Physics/Core/*.h Physics/Collision/*.h Physics/Utils/*.h)

add_executable(FlatPhysics main.cpp ${HeaderFiles} ${SourceFiles})
target_link_libraries(FlatPhysics SDL2::SDL2 SDL2::SDL2main)
