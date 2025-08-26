cmake_minimum_required(VERSION 3.16)
project(run)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(SDLIMAGE_AVIF OFF)

add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL3_image EXCLUDE_FROM_ALL)
add_subdirectory(SDL3_ttf EXCLUDE_FROM_ALL)

set(SOURCES main.cpp engine.cpp texturemanager.cpp warrior.cpp animation.cpp input.cpp timer.cpp IObject.h GameObject.h character.h warrior.h animation.h RigidBody.h input.h timer.h)
add_executable(run ${SOURCES})
target_include_directories(run PRIVATE "C:/billywilliamsd/ENGINE")

# Link to the actual SDL3 library.
target_link_libraries(run PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

target_compile_features(run PRIVATE cxx_std_17) 