project(physics)
cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
# Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")
# B2D - Box2D phyics library
set(BUILD_SHARED_LIBS OFF)  # Box2d does not specify SHARED or SATIC
add_subdirectory("lib/box2d")
set(B2D_INCS "lib/box2d/include")
link_directories("${CMAKE_BINARY_DIR}/lib/box2d/lib")

#### engine ####
add_library(engine STATIC engine/game_system.cpp engine/entity.cpp engine/tile_level_loader/level_system.cpp engine/renderer.cpp)
target_include_directories(engine INTERFACE tile_level_loader)
target_include_directories(engine PUBLIC engine)
target_link_libraries(engine sfml-graphics)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

#### Practical 5 ####
add_executable(physics "src/main.cpp" "src/scenes.cpp" "src/components.cpp" "src/b2d_utils.cpp")
target_include_directories(physics SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS} .)
target_link_libraries(physics engine sfml-graphics box2d)
set_target_properties(physics
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
 add_dependencies(physics copy_resources)
 set(EXECUTABLES ${EXECUTABLES} PRACTICAL_5_PHYSICS)
