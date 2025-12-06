# Snake Game Console

A simple ASCII-based Snake game implemented in C for console/terminal, utilizing `getch()` for capturing input and loops for continuous gameplay. This project aims to provide an engaging, easy-to-understand implementation of the classic Snake game, where the player controls a snake to collect food and avoid collisions.

---

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Gameplay](#gameplay)
- [Usage](#usage)
- [License](#license)
- [Contact](#contact)

---

## Description

**Snake Game Console** is a minimalistic, yet functional, console-based version of the classic Snake game, where the player controls a snake to eat food and grow longer while avoiding collisions with the walls and the snake's own body. The game is rendered using ASCII characters, and it relies on simple C standard libraries like `stdio.h` and `conio.h`.

This project uses the `getch()` function for reading keyboard input non-blocking, and it runs in a continuous game loop, with the game speed controlled by a basic timer.

---

## Features

- **Console-based**: Pure C, no external libraries or graphics.
- **Basic Gameplay**: Move the snake to collect food and avoid colliding with walls or its own body.
- **Game Over**: The game ends if the snake collides with the wall or itself.
- **Dynamic Difficulty**: Game speed is adjustable to provide a challenge.
- **Clean ASCII Art**: The game board and snake are drawn using basic ASCII characters for simplicity.

---

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/DeveloperJarvis/snake_game_console.git
   cd snake_game_console
   ```

2. **Compile the code**:

   If you're using GCC, you can compile the program by running:

   ```bash
   gcc -o snake_game main.c -lconio
   ```

   If you're using a different compiler, make sure you have access to `conio.h` or an equivalent method to handle `getch()`.

3. **Run the game**:

   After compiling, you can run the game with:

   ```bash
   ./snake_game
   ```

---

## Gameplay

- **Objective**: Control the snake to eat food and grow longer. Avoid hitting the walls and your own tail.

- **Controls**:

  - Use the **arrow keys** (Up, Down, Left, Right) to move the snake.
  - The snake moves continuously in the direction of the last input.

- **Game End**: The game ends when:

  - The snake runs into the wall.
  - The snake collides with its own body.

- **Score**: The score is based on how many pieces of food the snake eats. Each food item eaten increases the snake's length.

---

## Usage

After compiling and running the game, the screen will display the game board, with the snake, food, and walls. The game will continue to run in a loop, waiting for user input to move the snake.

- **Game Loop**: The game will continue until the snake collides with the walls or itself.
- **Speed Control**: The speed of the game is controlled by a delay function, allowing players to choose how fast the snake moves.

---

## License

This program is released under the **GNU General Public License (GPL) version 3**.

You are free to redistribute and modify the code under the terms of the license. However, there is **no warranty** for the software, and it is provided "as is" without any guarantee of merchantability or fitness for a particular purpose.

For more details, see the [GPL-3.0 License](https://www.gnu.org/licenses/gpl-3.0.html).

---

## Contact

Author: **Developer Jarvis** (Pen Name)
GitHub: [https://github.com/DeveloperJarvis](https://github.com/DeveloperJarvis)
Email: [developer.jarvis@example.com](mailto:developer.jarvis@example.com) _(optional)_

---

Feel free to modify and adapt the project to your needs. If you find any issues or have suggestions, feel free to open an issue or contribute to the repository!

## Creating tag

```bash
# 1. Check existing tags
git tag
# 2. Create a valid tag
git tag -a v1.0.0 -m "Release version 1.0.0"
# or lightweight tag
git tag v1.0.0
# push tag to remote
git push origin v1.0.0
```
