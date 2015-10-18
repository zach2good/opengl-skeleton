OpenGL Skeleton 
===

A no-fuss skeleton for creating OpenGL applications with SDL2, GLAD, GLM, ASSIMP, STB and Imgui.

1) Clone repo and submodules
```
git clone --recursive --progress -v "https://github.com/zach2good/opengl-skeleton.git"
```
2) Point CMake at it<br>
3) ???<br>
4) Profit<br>

Graphics Goals
===
* Billboarding Quads
* Texture Mapping
* Shadow Mapping
* Normal Mapping
* Displacement Mapping
* Reflection + Refraction
* Unified Mesh, Model, Texture and Material classes to be used with importing of MD2 (Model+Animations), MD5 (Model+Animations), Collada (Model+Animations) and OBJ (Model) file types. Generate Normal and Texture Coordinate information if the model doesn't already contain it.
* Small suite of basic primitives (Quad, Cube, Sphere, Teapot etc.) to be used as test objects .

Architecture Goals
===
* Entity Component System (ECS) design using EntityX (https://github.com/alecthomas/entityx) or similar.
* Implement Lua scripting system to be attached to entities to allow for live-scripting (http://www.executionunit.com/blog/2014/03/09/integrating-lua-and-my-c-game-engine/)
* Add Emscripten build for HTML target

Gameplay Goals
===
* Create test environment showcasing features
* Recreate Wolfenstein 3D basic functionality
<br>
<br>
![Screenshot](screenshot.png)
![Screenshot](lighting.gif)
