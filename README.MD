# ELEKS Chef
C++ camp graduation project

## About the program
ELEKS Chef is a simple cookbook application allowing the user to search for recipes in a culinary database and to modify the database by adding new recipes or editing existing ones. Recipes can also be marked as favorites.

The search can be performed by a substring of recipe's title, by national cuisine, by meal's course, by non-exclusive or exclusive subset of ingredients, by favorite status, as well as by any combination of the above criteria.

ELEKS Chef frontend program can be run both locally, as a standalone desktop application, and remotely, as a client application connecting to ELEKS Chef server.

ELEKS Chef comes with a database pre-filled with 28 sample recipes to get you started.

## Platform support and compatibility
ELEKS Chef can be built and run on Linux and Windows 10 platforms. As of the current version, the program can work with pure ASCII texts only.

## Obtaining ELEKS Chef
The program's source code as well as binaries installers are available through its [GitHub repository](https://github.com/Psyhich/eleks_camp_project).

## Building ELEKS Chef from source
### Requirements
* C++ compiler (supporting C++17)
* CMake (version 16 or higher)
* Qt5

### Linux
Install the requirements:
> `sudo apt-get install build-essential cmake qtbase5-dev git`

Clone the repository:
> `git clone https://github.com/Psyhich/eleks_camp_project`

Build the project:
> `cd eleks_camp_project ; mkdir build ; cd build/`

> `cmake .. ; make`

To run the frontend:
> `./frontend/eleks_chef_frontend`

To run the server:
> `./server/main/eleks_chef_server`

### Windows
In order to build this project on Windows, download and install [CMake](https://cmake.org/download/) and [Qt](https://www.qt.io/download-open-source) version 5 or higher. 

Make sure that your PATH environment variable contains the path to Qt's binary directory. The corresponding line should look similar to the following:

> `C:\Qt\"version"\"your compiler"\bin`

Clone the repository by navigating in your terminal to the desirable location and running:

> `git clone https://github.com/Psyhich/eleks_camp_project`

To build, open your terminal, navigate to the cloned repository's root directory and run the following commands.

Create and change to build directory:
> `mkdir build ; cd build/`

Configure cmake and compile the project:

> `cmake ..`

> `cmake --build ./`

To run the frontend:
> `"project_root"\build\frontend\"your_build_profile"\eleks_chef_frontend`

To run the server:
> `"project_root"\build\server\main\"your_build_profile"\eleks_chef_server`

## Binaries installation
Alternatively, you may install precompiled binaries via installers which can be found in the `release` subdirectory of the repository.