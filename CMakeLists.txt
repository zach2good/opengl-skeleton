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

src/graphics/imgui/imgui.h
src/graphics/imgui/imgui.cpp
src/graphics/imgui/imgui_draw.cpp
src/graphics/imgui/imgui_impl_sdl.h
src/graphics/imgui/imgui_impl_sdl.cpp

src/graphics/stb/stb_image.h

src/graphics/Shader.h
src/graphics/Shader.cpp
src/graphics/ShaderManager.h
src/graphics/ShaderManager.cpp

src/graphics/RawModel.h
src/graphics/RawModel.cpp
src/graphics/Loader.h
src/graphics/Loader.cpp

src/graphics/Window.h
src/graphics/Window.cpp

src/graphics/Renderer.h
src/graphics/Renderer.cpp

src/utils/DebugUi.h
src/utils/DebugUi.cpp
)

include_directories(src)

# executables
add_executable(main ${SOURCE_FILES})
target_link_libraries(main SDL2-static SDL2main libglew_static)