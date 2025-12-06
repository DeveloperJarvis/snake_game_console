// --------------------------------------------------
// -*- C -*- Compatibility Header
//
// Copyright (C) 2023 Developer Jarvis (Pen Name)
//
// This file is part of the snake_game_console Library. This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// SPDX-License-Identifier: GPL-3.0-or-later
//
// snake_game_console - Simple ASCII snake using getch() and loops
//
// Author: Developer Jarvis (Pen Name)
// Contact: https://github.com/DeveloperJarvis
//
// --------------------------------------------------
#ifndef SNAKE_GAME_CONSOLE_H
#define SNAKE_GAME_CONSOLE_H

// --------------------------------------------------
// Constanst and macros
// --------------------------------------------------
#define BOARD_WIDTH 20	  // Width of the game board
#define BOARD_HEIGHT 20	  // Height of the game board
#define INIT_SNAKE_SIZE 3 // Initial size of the snake

#define EMPTY_SPACE ' ' // Empty space character
#define WALL '#'		// Wall character
#define SNAKE_HEAD '@'	// Snake head character
#define SNAKE_BODY '*'	// Snake body character
#define FOOD '$'		// Food character

// Direction constants
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// --------------------------------------------------
// Date Structures
// --------------------------------------------------

// Snake body segment
typedef struct
{
	int x, y; // Position of a segment
} SnakeSegment;

// Snake structure
typedef struct
{
	SnakeSegment head;	// Head of the snake
	SnakeSegment *body; // Body segments array
	int length;			// Length of the snake
	int direction;		// Current movement direction
} Snake;

// Food structure
typedef struct
{
	int x, y; // Position of the food
} Food;

// Game Environment
typedef struct
{
	char board[BOARD_HEIGHT][BOARD_WIDTH]; // The game board
	Snake snake;						   // The snake object
	Food food;							   // The food object
	int score;							   // Current score
} GameEnv;

// --------------------------------------------------
// forward function declarations/ prototypes
// --------------------------------------------------

// Helper display functions
void display_help(const char *s);	 // Displays help options
void display_version(const char *s); // Displays game version

// Core game function
void snake_game();

// Game Environment Functions
void init_game(GameEnv *game);	  // Initializes the game state
void render_board(GameEnv *game); // Renders the game board
void spawn_food(GameEnv *game);	  // Spawns food at a random position
void render_snake(GameEnv *game); // Renders the snake
void render_food(GameEnv *game);  // Renders the food

// Sanke Functions
void move_snake(GameEnv *game);			   // Moves the snake based on the current direction
void grow_snake(GameEnv *game);			   // Grows the snake when it eats food
int check_collision(GameEnv *game);		   // Checks for collisions with the walls or self
void update_snake_position(GameEnv *game); // Updates the positions of the snake's body

// Input Handling Functions
char get_input(GameEnv *game); // Captures user input (non-blocking)

// Game Logic Functions
void game_update(GameEnv *game); // Updates the game state (movement, food, etc)
void game_over(GameEnv *game);	 // Ends the game

// Timer
void delay(int milliseconds); // Introduces a game delay (game speed)

// Linux Windows compatible non-blocking keyboard input
void enable_raw_mode();
void disable_raw_mode();
int kbhit();
int getch();
#endif // SNAKE_GAME_CONSOLE_H
