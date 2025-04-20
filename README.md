# No Name Engine or !NE

---

## How to clone the project

This project has some third_party lib dependencies like:
- bullet-physics sdk
- glfw
- glew
- OpenGL
- Filament
- SpdLog

you must clone the project and initialize the .gitmodules

`git clone --recursive https://github.com/Raphalsk050/NNEngine.git`

Note: if you already have cloned the project, to initialize the gitmodules use:

`git submodule update --init --recursive`

---

## How to build

To build the project you must give permission to sh script
### **On unix based systems**
`chmod +x build.sh`

### This script have three possibilities:

- build - build the project inside the build directory
- clean - remove all the build directory
- run - run the binary inside the build/bin directory

### To run the project, only run the following command:
`./build.sh run`

---
