# Slot Machine Simulator - PCLP Assignment 1

This project is an arcade-style **slot machine simulator** implemented in C, created as part of the first programming assignment for the _Computer Programming_ course (PCLP).

The simulator mimics the behavior of a real slot machine, allowing for operations such as rotating columns, detecting winning combinations, computing scores, and running optimizations. The code is fully modular and relies on dynamically allocated memory for all matrix operations, in compliance with the assignment's requirements.

## Features

- Dynamic 2D matrix manipulation
- Slot column rotation
- Winning combination detection (horizontal lines, diagonals, and intersections)
- Score calculation with combo and symbol bonuses
- Move simulations and optimizations (maximizing score through edits or rotations)
- Pathfinding in a cost matrix using BFS (Lee algorithm)

## Task Overview and Implementation

### 🔄 Task 1: Spin the... Pixels?
**Objective:** Rotate a given column by a number of positions (downwards, circularly).  
**Implementation:**  
Used a dynamically allocated temporary vector to store and shift column elements before copying them back to the matrix.

### 🎰 Task 2: The Game Might Be Rigged...
**Objective:** Identify all valid winning combinations in the top 3 rows (the game "panel") and compute the total score.  
**Implementation:**
- Used a frequency vector to count distinct symbols in the panel.
- Searched for the longest horizontal sequences and both diagonal types.
- Carefully handled intersection cases ("X" shapes).
- Applied score multipliers for special symbols (e.g., 7) and added bonus scores based on symbol diversity.

### 🔁 Task 3: All In
**Objective:** Perform a sequence of column rotations and sum up the intermediate scores after each step.  
**Implementation:**  
Reused the logic from Task 1 and Task 2 to apply rotations and recompute scores iteratively.

### ✏️ Task 4: So Close!
**Objective:** Determine the maximum score obtainable by changing a single symbol in the panel.  
**Implementation:**  
For every position in the panel, tested all possible replacements (0–9), evaluated the resulting score, and kept the maximum.

### 🔧 Task 5: What If...?
**Objective:** Find the best possible score obtainable by rotating any two columns by any number of positions.  
**Implementation:**  
Tested every pair of columns and every possible pair of rotation values. Used Task 1 to apply rotations and Task 2 to compute scores. Pruned unnecessary operations by skipping symmetrical duplicates where possible.

### 🧩 Task 6 (Bonus): 99% of Gamblers Quit Before They Win
**Objective:** Find the minimum cost path from the top-left to the bottom-right corner of the 3×M panel, where the cost is the absolute difference from the initial symbol.  
**Implementation:**  
Used a BFS-based shortest path algorithm (Lee's algorithm) with a dynamically allocated queue to track positions and compute the minimal path cost.

## Structure

- `main.c`: Entry point and task dispatcher
- `utils.c` / `utils.h`: Matrix helpers and common operations
- `Makefile`: Standard makefile for compilation (`make`, `make run`, `make clean`)
- `README.md`: Current file

## Build & Run

```bash
make           # Compiles the project
./tema1        # Runs the program
```

## Notes

- All memory was **dynamically allocated and properly freed**.
- Coding style **adheres to the Cpp Core Guidelines**.
- All tasks **passed the Moodle checker** with a score of **100/100**.

## Course Info

📚 **Programming Calculators (CB & CD)** — 2024  
🧠 **Task Score:** 100/100
