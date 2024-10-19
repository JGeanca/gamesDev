# Game T02

## Description

**Spoiler!**

This is a basic game that tries to provide a high level of difficulty, where players typically die multiple times before managing to clear each level. The game incorporates the following key features:

- Collision mechanics
- Respawn system
- Checkpoints
- Enemy patterns behaviors
- Death counter
- Flag points

For now, the game has only tree levels, but it is possible to add more levels with new mechanics in the future.

## How to Play

The objective of the game is to reach all the flag points to unlock the win condition. To do so, you must avoid the enemies and obstacles that will try to kill you. If you die, you will respawn at the last checkpoint you reached.

### Controls

Player Movement:

- **W**: Move up
- **A**: Move left
- **D**: Move right
- **S**: Move down

UI Controls:

- **ESC**: Quit the game
- **P**: Pause the game
- **M**: Mute the game

Menu:

Use mouse (left click) to navigate through the menu and levels.

### Design UML

![UML_Diagram](./design/GameEngineUML.svg)

To see the diagram in more detail [click here](https://drive.google.com/file/d/1zphKNW7CagGxb6O-eT8wpsbV8bpayV1j/view?usp=drive_link)

## User Manual

### Requirements

To run the program, you need a Linux terminal and the following libraries installed:

- libsdl2-dev
- libsdl2-image-dev
- libsdl2-ttf-dev
- libsdl2-mixer-dev
- liblua5.3-dev

## Installation

You can install the required libraries by running the following command in the terminal:

~~~bash
sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev liblua5.3-dev
~~~

### Compilation and Execution

To compile and run the program, use the following command:

~~~bash
make run
~~~

To clean the project, use the following command:

~~~bash
make clean
~~~

To compile and run the program in **debug mode**, use the following command:

~~~bash
make run-d
~~~

**Note**: The debug mode only works if the program wasn't compiled before. Make sure to run `make clean` before running the debug mode if the program was already compiled.

#### Compile with Sanitizers

##### Sanitizer requirements

To compile with sanitizers, you need to have the `clang` compiler installed. You can install it by running the following command:

~~~bash
sudo apt-get install clang
~~~

and also you need to have the `valgrind` tool installed. You can install it by running the following command:

~~~bash
sudo apt-get install valgrind
~~~

##### Compilation

To compile and run the program with **AddressSanitizer** enabled, use the following command:

~~~bash
make asan
~~~

To compile and run the program with **MemorySanitizer** enabled, use the following command:

~~~bash
make msan
~~~

To compile and run the program with **UndefinedBehaviorSanitizer** enabled, use the following command:

~~~bash
make ubsan
~~~

To compile and run the program with **ValgrindMemcheck** enabled, use the following command:

~~~bash
make memcheck
~~~

### Documentation

#### Doc Requirements

To generate code documentation, you need to have the `doxygen` tool installed. You can install it by running the following command:

~~~bash
sudo apt-get install doxygen
~~~

To generate the documentation, use the following command:

~~~bash
make docs
~~~

The documentation will be available in the `doc` folder in the root directory.
**Note**: The command generates multiple files, but the main file is `index.html` open it in your browser to see the documentation.
