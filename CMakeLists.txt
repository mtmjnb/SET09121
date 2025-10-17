project(pacman)
cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")

#### level system ####
add_library(engine STATIC engine/game_system.cpp engine/entity.cpp engine/tile_level_loader/level_system.cpp "engine/renderer.cpp")
target_include_directories(engine INTERFACE tile_level_loader)
target_include_directories(engine PUBLIC engine)
target_link_libraries(engine sfml-graphics)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

#### Practical 5 ####
add_executable(pacman "src/main.cpp" "src/player.cpp" "src/scenes.cpp" "engine/renderer.cpp")
target_include_directories(pacman PRIVATE ${SFML_INCS} .)
target_link_libraries(pacman engine sfml-graphics)
set_target_properties(pacman 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
 add_dependencies(pacman copy_resources)