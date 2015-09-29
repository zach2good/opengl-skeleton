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

src/entities/Camera.h
src/entities/Camera.cpp
src/entities/Entity.h
src/entities/Light.h

src/graphics/imgui/imgui.h
src/graphics/imgui/imgui.cpp
src/graphics/imgui/imgui_draw.cpp
src/graphics/imgui/imgui_impl_sdl.h
src/graphics/imgui/imgui_impl_sdl.cpp

src/graphics/models/RawModel.h
src/graphics/models/TexturedModel.h

src/graphics/shaders/ShaderProgram.h
src/graphics/shaders/ShaderProgram.cpp
src/graphics/shaders/BasicShader.h
src/graphics/shaders/BasicShader.cpp

src/graphics/stb/stb_image.h

src/graphics/textures/ModelTexture.h

src/graphics/Loader.h
src/graphics/Loader.cpp

src/graphics/Renderer.h
src/graphics/Renderer.cpp

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
target_link_libraries(main SDL2-static SDL2main libglew_static)