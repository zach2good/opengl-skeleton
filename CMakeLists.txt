cmake_minimum_required(VERSION 3.0)
project(Skeleton)

option(DIRECTX OFF)
add_subdirectory(lib/sdl)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(lib/assimp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MTd -O2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11 -O2")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(include/
                    lib/assimp/include/
                    lib/glad/include/
                    lib/sdl/include/
                    lib/glm/
                    lib/stb/)

file(GLOB VENDORS_SOURCES lib/glad/src/glad.c)

file(GLOB PROJECT_HEADERS src/*.hpp
						              src/*.h
                          src/*/*.hpp
                          src/*/*.h)

file(GLOB PROJECT_SOURCES src/*.cpp
                          src/*/*.cpp
                          src/*/*/*.cpp
                          src/*/*/*/*.cpp)

file(GLOB PROJECT_SHADERS res/shaders/*.glsl
                          res/shaders/*.comp
                          res/shaders/*.frag
                          res/shaders/*.geom
                          res/shaders/*.vert)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})

target_link_libraries(${PROJECT_NAME} assimp SDL2-static SDL2main
                      ${SDL2_LIBRARIES} ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})