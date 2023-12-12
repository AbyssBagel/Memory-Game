# Memory Game in C

## Introduction
This is a simple memory game implemented in C, created when I was in first year. The purpose of this project is to practice programming skills, particularly in the context of memory manipulation.

## Overview
The game initializes a grid with customizable rows and columns and fills it with pairs of characters. The objective is to match pairs by revealing two cells at a time. The game continues until all pairs are found or the maximum number of attempts is reached.

## Features
- Customizable grid size (rows and columns)
- Random shuffling of character pairs on the grid
- User interaction to select and reveal cells
- Colorful console output using ANSI escape codes on Unix-like systems and Windows console functions on Windows

## How to Play
1. Run the executable
2. Enter the number of rows and columns for the grid when prompted
3. The game will display the initial grid, shuffle the pairs, and briefly show the grid
4. Players take turns selecting two cells by entering their row and column coordinates
5. The game reveals the selected cells and checks for a match
6. The game continues until all pairs are found or the maximum number of attempts is reached

## Compilation and Execution
To compile the program, use a C compiler such as GCC:

```bash
gcc Memory.c -o memory_game
```
To run the compiled executable:
```bash
./Memory
```

# Platform

The game is designed to run on both Unix-like systems (Linux, macOS) and Windows

# Acknowledgments

- The colorization functions are platform-specific for Unix-like systems and Windows
- The project uses ANSI escape codes for terminal colorization on Unix-like systems

# Author

AbyssBagel aka Antonin G.

# License

This project is licensed under the [CC BY-NC-SA 4.0 License](https://creativecommons.org/licenses/by-nc-sa/4.0/)
