cmake_minimum_required(VERSION 3.25)
project(assignment2)

set(CMAKE_CXX_STANDARD 17)

# Set the path to SFML include directory
set(SFML_INCLUDE_DIR /opt/homebrew/Cellar/sfml/2.6.1/include)

# Set the path to SFML library directory
set(SFML_LIBRARY_DIR /opt/homebrew/Cellar/sfml/2.6.1/lib)

# Find SFML
find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)

# Add your source files
add_executable(assignment2 main.cpp vec2.cpp vec2.h components.h entity_manager.cpp entity_manager.h entity.h game.cpp game.h math.cpp math.h)

# Include SFML headers
target_include_directories(assignment2 PRIVATE ${SFML_INCLUDE_DIR})

# Link SFML libraries to your executable
target_link_libraries(assignment2 PRIVATE sfml-graphics sfml-audio)
