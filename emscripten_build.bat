emcc src/main.cpp src/graphics/Window.cpp src/core/Input.cpp -std=c++11 -w -s ASSERTIONS=1 -O2 -I lib/glm -s USE_SDL=2 -s FULL_ES2=1 -o embuild/game.html
