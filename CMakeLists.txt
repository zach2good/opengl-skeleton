cmake_minimum_required (VERSION 2.8)
project (opengl-skeleton)

# put the executable into the bin directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# c++14 activation
list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

# compilation flags
add_definitions(-Wall)

# sdl2
add_subdirectory(lib/sdl2)
include_directories(lib/sdl2/include)

# glew
add_definitions(-DGLEW_STATIC)
option(glew-cmake_BUILD_SHARED "" OFF)
add_subdirectory(lib/glew)
include_directories(lib/glew/include lib/glew/src)

# glm
include_directories(lib/glm)

# reference source
set(SOURCE_FILES 

src/main.cpp 

src/graphic/imgui/imgui.h
src/graphic/imgui/imgui.cpp
src/graphic/imgui/imgui_draw.cpp
src/graphic/imgui/imgui_impl_sdl.h
src/graphic/imgui/imgui_impl_sdl.cpp

src/utils/DebugUi.h
src/utils/DebugUi.cpp
)

include_directories(src)

# executables
add_executable(main ${SOURCE_FILES})
target_link_libraries(main SDL2-static SDL2main libglew_static)