emcc src/main.cpp src/graphics/Window.cpp src/graphics/DebugUi.cpp src/graphics/ShaderProgram.cpp src/core/Input.cpp src/imgui/imgui.cpp src/imgui/imgui_draw.cpp src/imgui/imgui_impl_sdlems.cpp -std=c++11 -w -s ASSERTIONS=1 -O2 -I lib/glm -I lib/assimp/include -I src/imgui -s USE_SDL=2 -s FULL_ES3=1 -s USE_WEBGL2=0 --preload-file res -o embuild/game.html
