# Eleks-chef
Project work on eleks C++ camp

## Requirements
* C++ compiler
* CMake
* Qt5

## Building
### Linux
Firstly installing requirements
> `sudo apt-get install build-essential cmake qtbase5-dev git`

Clonning repository
> `git clone https://github.com/Psyhich/eleks_camp_project`

Run these commands to build project
> `cd eleks_camp_project ; mkdir build ; cd build/`

> `cmake .. ; make`

To run frontend
> `./frontend/eleks_chef_frontend`

And to run server
> `./server/main/eleks_chef_server`

### Windows
To build this project on Windows, you shold download [CMake](https://cmake.org/download/) and [Qt](https://www.qt.io/download-open-source) with version higher than 5. 

Be sure that path to Qt is written in your PATH enviroment variable, it should look like this:

> `C:\Qt\"version"\"your compiler"\bin`

After downloading sources, open powershell in sources folder and type:

> `mkdir build ; cd build/`

Then, you should configure cmake and compile the project:

> `cmake ..`

> `cmake --build ./`

Builded files should be located in:

server:
> `project_root\build\server\main\your_build_profile\eleks_chef_server`

frontend:
> `project_root\build\frontend\your_build_profile\eleks_chef_frontend`
