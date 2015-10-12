OpenGL Skeleton 
===

A no-fuss skeleton for creating OpenGL applications with SDL2, GLEW, GLM, ASSIMP, SOIL and Imgui.

1) Clone repo and submodules
```
git clone --recursive --progress -v "https://github.com/zach2good/opengl-skeleton.git"
```
2) Point CMake at it.<br>
3) ???<br>
4) Profit.<br>

TODO
===
* Work through basic examples in books and online to build functionality
* Make robust basic functionality (Default shaders, test scene, OBJ Loader etc.)

Goals
===
* MD5 Models and Animations (Doom3 Models)
* Collada Models and Animations
* Billboarding quads (+Animated Textures on them)
* Remake Wolfenstein 3D 
* Entity Component System (ECS) design using EntityX (https://github.com/alecthomas/entityx) or similar
* Implement Lua scripting system to be attached to entities to allow for live-scripting (http://www.executionunit.com/blog/2014/03/09/integrating-lua-and-my-c-game-engine/)
* Add Emscripten build for HTML target

![Screenshot](screenshot.png)

