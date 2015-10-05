OpenGL Skeleton 
===

A no-fuss skeleton app for creating OpenGL applications with SDL2, GLEW, GLM, SOIL and Imgui.

1) Clone repo and submodules
```
git clone --recursive --progress -v "https://github.com/zach2good/opengl-skeleton.git"
```
2) Point CMake at it.
3) ???
4) Profit.

TODO
===
* Work through basic examples in books and online to build functionality
* Make robust basic functionality (Default shaders, test scene, OBJ Loader etc.)

![Screenshot](screenshot.png)

Troubleshooting
===

When doing your CMake build if you are faced with this error:<br>
![Error1](err1.png)

Click through it and <b>untick "DirectX"</b>.<br>
![Error2](err2.png)

You will then be able to continue your build.<br>
