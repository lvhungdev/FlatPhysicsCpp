cmake_minimum_required(VERSION 3.26)
project(FlatPhysics)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

if (MSVC)
    include_directories(FlatPhysics . Physics)
else ()
    include_directories(FlatPhysics . Physics ${SDL2_INCLUDE_DIRS})
endif ()

file(GLOB SourceFiles Renderer/*.cpp Physics/*.cpp Physics/Core/*.cpp Physics/Collision/*.cpp Physics/Utils/*.cpp)
file(GLOB HeaderFiles Renderer/*.h Physics/*.h Physics/Core/*.h Physics/Collision/*.h Physics/Utils/*.h)

add_executable(FlatPhysics main.cpp ${HeaderFiles} ${SourceFiles})

if (MSVC)
    target_link_libraries(FlatPhysics SDL2::SDL2 SDL2::SDL2main)
else ()
    target_link_libraries(FlatPhysics ${SDL2_LIBRARIES})
endif ()
