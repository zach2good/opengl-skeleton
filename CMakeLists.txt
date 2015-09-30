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

# glm
include_directories(lib/soil/src)
add_subdirectory(lib/soil)


# reference source
set(SOURCE_FILES 

src/entities/Camera.h
src/entities/Camera.cpp
src/entities/Entity.h
src/entities/Light.h

src/graphics/imgui/imgui.h
src/graphics/imgui/imgui.cpp
src/graphics/imgui/imgui_draw.cpp
src/graphics/imgui/imgui_impl_sdlogl3.h
src/graphics/imgui/imgui_impl_sdlogl3.cpp

src/graphics/models/Mesh.h
src/graphics/models/Mesh.cpp

src/graphics/shaders/ShaderProgram.h
src/graphics/shaders/ShaderProgram.cpp

src/graphics/textures/Texture.h

src/graphics/BasicRenderer.h
src/graphics/BasicRenderer.cpp
src/graphics/Loader.h
src/graphics/Loader.cpp
src/graphics/OBJLoader.h
src/graphics/OBJLoader.cpp
src/graphics/Window.h
src/graphics/Window.cpp

src/utils/Maths.h
src/utils/Maths.cpp

src/utils/DebugUi.h
src/utils/DebugUi.cpp

src/main.cpp 
)

include_directories(src)

# executables
add_executable(main ${SOURCE_FILES})
target_link_libraries(main SDL2-static SDL2main libglew_static SOIL)