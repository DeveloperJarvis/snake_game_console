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

// --------------------------------------------------
// header files
// --------------------------------------------------
#include <stdio.h>	// for printf()
#include <string.h> // for strcmp()
#include <time.h>	// for time()
#include <stdlib.h> // for rand(), srand()

#if defined(_WIN32) | defined(_WIN64)
#include <windows.h> // for Sleep()
#include <conio.h>	 // for getch(), kbhit()
#endif

#include "snake_game_console.h"

// --------------------------------------------------
// main function
// --------------------------------------------------
int main(int argc, char *argv[])
{
	if (argc == 1)
		snake_game();
	else if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
		display_help(argv[0]);
	else if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0))
		display_version(argv[0]);
	else
	{
		printf("Invalid input\n");
		display_help(argv[0]);
	}
	return 0;
}

// --------------------------------------------------
// Helper display functions
// --------------------------------------------------

// Displays help options
void display_help(const char *s)
{
	printf("Usage: %s [options]\n", s);
	printf(" -h --help\tDisplay help options\n");
	printf(" -v --version\tDisplay program version\n");
	printf("Happy playing!...\n");
}

// Displays game version
void display_version(const char *s)
{
	printf("%s version: 1.0.0\n", s);
}

// --------------------------------------------------
// Core game function
// --------------------------------------------------
void snake_game()
{
	enable_raw_mode(); // <--- requied on Linux
	GameEnv game;
	init_game(&game);

	while (1)
	{
		game_update(&game);

		if (check_collision(&game))
		{
			disable_raw_mode(); // <--- requied on Linux
			game_over(&game);
		}

		render_board(&game);
		delay(10);
	}
}

// --------------------------------------------------
// Game Environment Functions
// --------------------------------------------------

// Initializes the game state
void init_game(GameEnv *game)
{
	game->score = 0;

	// Allocate snake body array
	// Max snake length
	game->snake.body = malloc(sizeof(SnakeSegment) * 200);
	if (game->snake.body == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(1);
	}

	// Clear board
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			game->board[i][j] = EMPTY_SPACE;

	// Walls
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		game->board[i][0] = WALL;
		game->board[i][BOARD_WIDTH - 1] = WALL;
	}
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		game->board[0][j] = WALL;
		game->board[BOARD_HEIGHT - 1][j] = WALL;
	}

	// Initialize snake
	game->snake.length = INIT_SNAKE_SIZE;
	game->snake.direction = RIGHT;

	int cx = BOARD_WIDTH / 2;
	int cy = BOARD_HEIGHT / 2;

	game->snake.head.x = cx;
	game->snake.head.y = cy;

	for (int i = 0; i < game->snake.length; i++)
	{
		game->snake.body[i].x = cx - i;
		game->snake.body[i].y = cy;
	}

	// Initialize food
	spawn_food(game);
}

// Renders the game board
void render_board(GameEnv *game)
{
#if defined(_WIND32) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif

	render_food(game);
	render_snake(game);

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
			printf("%c", game->board[i][j]);
		printf("\n");
	}

	printf("\n Score: %d\n", game->score);

	// Reset dynamic positions
	for (int i = 0; i < BOARD_HEIGHT; i++)
		for (int j = 0; j < BOARD_WIDTH; j++)
			if (game->board[i][j] != WALL)
				game->board[i][j] = EMPTY_SPACE;
}

// Spawns food at a random position
void spawn_food(GameEnv *game)
{
	srand(time(NULL));
	int x, y;

	while (1)
	{
		x = rand() % (BOARD_WIDTH - 2) + 1;
		y = rand() % (BOARD_HEIGHT - 2) + 1;

		int ok = 1;

		if (x == game->snake.head.x && y == game->snake.head.y)
			ok = 0;

		for (int i = 0; i < game->snake.length; i++)
			if (x == game->snake.body[i].x && y == game->snake.body[i].y)
				ok = 0;

		if (ok)
			break;
	}

	game->food.x = x;
	game->food.y = y;
}

// Renders the snake
void render_snake(GameEnv *game)
{
	game->board[game->snake.head.y][game->snake.head.x] = SNAKE_HEAD;

	for (int i = 0; i < game->snake.length; i++)
		game->board[game->snake.body[i].y][game->snake.body[i].x] = SNAKE_BODY;
}

// Renders the food
void render_food(GameEnv *game)
{
	game->board[game->food.y][game->food.x] = FOOD;
}

// --------------------------------------------------
// Sanke Functions
// --------------------------------------------------

// Moves the snake based on the current direction
void move_snake(GameEnv *game)
{
	update_snake_position(game);

	switch (game->snake.direction)
	{
	case UP:
		game->snake.head.y--;
		break;
	case DOWN:
		game->snake.head.y++;
		break;
	case LEFT:
		game->snake.head.x--;
		break;
	case RIGHT:
		game->snake.head.x++;
		break;
	}
}

// Grows the snake when it eats food
void grow_snake(GameEnv *game)
{
	// overflow memory protection
	if (game->snake.length < 200)
		game->snake.length++;
}

// Checks for collisions with the walls or self
int check_collision(GameEnv *game)
{
	int x = game->snake.head.x;
	int y = game->snake.head.y;

	// Wall collision
	if (x == 0 || x == BOARD_WIDTH - 1 || y == 0 || y == BOARD_HEIGHT - 1)
		return 1;

	// Self collision
	for (int i = 0; i < game->snake.length; i++)
		if (x == game->snake.body[i].x && y == game->snake.body[i].y)
			return 1;

	return 0;
}

// Updates the positions of the snake's body
void update_snake_position(GameEnv *game)
{
	for (int i = game->snake.length - 1; i > 0; i--)
		game->snake.body[i] = game->snake.body[i - 1];

	game->snake.body[0] = game->snake.head;
}

// --------------------------------------------------
// Input Handling Functions
// --------------------------------------------------

// Captures user input (non-blocking)
char get_input(GameEnv *game)
{
	if (kbhit())
	{
		char c = getch();
		switch (c)
		{
		case 'w':
			if (game->snake.direction != DOWN)
				game->snake.direction = UP;
			break;
		case 's':
			if (game->snake.direction != UP)
				game->snake.direction = DOWN;
			break;
		case 'a':
			if (game->snake.direction != RIGHT)
				game->snake.direction = LEFT;
			break;
		case 'd':
			if (game->snake.direction != LEFT)
				game->snake.direction = RIGHT;
			break;
		}

		// Optional: arrow key support (Linux gives escape sequence)
		if (c == 27 && kbhit()) // Escape sequence
		{
			getch();	 // skip '['
			c = getch(); // real arrow code
			if (c == 'A')
				game->snake.direction = UP;
			if (c == 'B')
				game->snake.direction = DOWN;
			if (c == 'D')
				game->snake.direction = LEFT;
			if (c == 'C')
				game->snake.direction = RIGHT;
		}
	}
	return 0;
}

// --------------------------------------------------
// Game Logic Functions
// --------------------------------------------------

// Updates the game state (movement, food, etc)
void game_update(GameEnv *game)
{
	get_input(game);
	move_snake(game);

	// Eat food
	if (game->snake.head.x == game->food.x &&
		game->snake.head.y == game->food.y)
	{
		game->score++;
		grow_snake(game);
		spawn_food(game);
	}
}

// Ends the game
void game_over(GameEnv *game)
{
#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif
	printf("\n===== GAME OVER =====\n");
	printf("Final Score: %d\n", game->score);
	printf("=====================\n");

	disable_raw_mode();

	free(game->snake.body);

	exit(0);
}

// --------------------------------------------------
// Timer
// --------------------------------------------------

// Introduces a game delay (game speed)
void delay(int milliseconds)
{
	/*
	Busy-wait method drawback: using 100% CPU
	// Storing starting time
	// clock_t: clock_t represents the processor time and \
	// 				is used to measure the CPU clock cycles
	clock_t start_time = clock();
	// CLOCKS_PER_SEC: is usually 1000 or 1,000,000 depending on system
	clock_t wait_ticks = milliseconds * (CLOCKS_PER_SEC / 1000);
	// loop will run until time is not achieved
	while (clock() < start_time + wait_ticks)
		;
	*/

#if defined(_WIN32) | defined(_WIN64)
	Sleep(milliseconds);
#else
	struct timespec ts;
	ts.tv_sec = milliseconds / 1000;
	ts.tv_nsec = (milliseconds % 1000) * 1000000;
	nanosleep(&ts, NULL);
#endif
}

// --------------------------------------------------
// Linux & Windows compatible non-blocking keyboard input
// --------------------------------------------------
#if defined(_WIN32) || defined(_WIN64)
// -------------- WINDOWS VERSION -------------------
#include <conio.h>
void enable_raw_mode()
{
}

void disable_raw_mode()
{
}

int kbhit()
{
	return _kbhit();
}

int getch()
{
	return _getch();
}

#else
// -------------- LINUX VERSION -------------------

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

static struct termios orig_termios;

// Enable raw (non-cannonical, no-echo) mode
void enable_raw_mode()
{
	tcgetattr(STDIN_FILENO, &orig_termios);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

// Restore terminal state
void disable_raw_mode()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

// Check if key is pressed (non-blocking)
int kbhit()
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

// Get single key without waiting
int getch()
{
	int ch;
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}

#endif