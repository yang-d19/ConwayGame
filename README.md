# Conway Game

Author: Ding Yang

Email: dingtc01@gmail.com

## Introduction

You can specify initial patterns, whether defined in source code or in data file, to start the game.

In source code:
1. glider
2. toad
3. gosper glider gun


Multiple adjustable parameters are available when running the game, include:
- maximum running steps (-1 means infinite steps)
- interval between two frame
- x width and y width of the displaying window
- whether allow display window to dynamicly fit the universe or not

## How to Run

```
$ make all
$ ./bin/main
```

## Demo

### 1. Glider
![gliber](media/glider.gif)

### 2. Gosper Glider Gun

![gosperglidergun](media/gosper_glider_gun.gif)

## Code Structure

```
📂 project_root
├── 📂 bin                 // executable target
├── 📂 data                // universe input and output
├── 📂 media               // screenshot or gif
├── 📂 obj                 // compiling objects
├── 📂 src
│   ├── 📄 displayer.cpp   // How to display the game
│   ├── 📄 displayer.hpp 
│   ├── 📄 game.cpp        // How the universe updates by game logic
│   ├── 📄 game.hpp
│   ├── 📄 main.cpp        // Entrance
│   └── 📄 utils.hpp
├── 📄 Makefile
└── 📄 README.md
```