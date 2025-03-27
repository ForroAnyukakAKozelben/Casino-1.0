# Roulette Casino Simulation

This project is a C++ simulation of a casino roulette game. The game creates a configurable number of bot players, assigns each a random starting coin balance (based on a user-provided average), and lets them place various types of bets. The game runs turn by turn until only one player remains with a positive balance.

## Overview

- **Roulette Game:**  
  A roulette wheel is simulated using a table of color-number pairs. Each turn, the wheel is spun and a winning tile is selected randomly.

- **Player Bets:**  
  Players can place a variety of bets, each with its own payout multiplier:
  - **StraightUp:** Betting on a single number (35:1 payout).
  - **Split:** Betting on two adjacent numbers (17:1 payout).
  - **Street:** Betting on three numbers in a row (11:1 payout).
  - **Corner:** Betting on four numbers that form a square (8:1 payout).
  - **Basket:** Betting on the numbers 0, "00", 1, 2, and 3 (6:1 payout, American Roulette only).
  - **Line:** Betting on six numbers (two consecutive rows, 5:1 payout).
  - **Column:** Betting on one of three columns (2:1 payout).
  - **Dozen:** Betting on one of three dozens (2:1 payout).
  - **EvenOdd:** Betting on even or odd numbers (1:1 payout).
  - **RedBlack:** Betting on red or black (1:1 payout).

- **Game Loop:**  
  The simulation continues with all players placing random bets until only one player remains with a positive balance. A 3‑second pause between turns lets you follow the progress of the game.

## Features

- **Configurable Setup:**  
  The user is prompted to specify:
  - The number of players.
  - The average starting coins per player.
  
  Each player's starting balance is then randomly varied between half and 1.5× the provided average.

- **Random Betting:**  
  Every turn, each active player is assigned a random bet among all available bet types using predefined overloads in the `Player` class.

- **Casino and Roulette Integration:**  
  The project is organized into three main classes:
  - **Player:** Represents a player with a name, balance, and bet.
  - **Casino:** Maintains a list of players.
  - **Roulette:** Simulates the roulette wheel, processes bets, and computes winnings.

- **Bet Evaluation and Payout:**  
  Each bet type has a predefined payout multiplier. When the roulette wheel is spun, the winning tile is compared to each player's bet. If the bet wins, the player's balance is increased by the wager multiplied by the bet's multiplier.

## Requirements

- **C++17 or later:**  
  The project uses modern C++ features (e.g., `std::variant` is replaced by a custom `Bet` struct) and requires a C++17-compliant compiler.

- **Standard C++ Libraries:**  
  No external dependencies are required beyond the standard libraries.

## How to Build and Run

1. **Clone the Repository:**  
   Download or clone the repository containing the source files:
   - `Player.hpp` / `Player.cpp`
   - `Casino.hpp` / `Casino.cpp`
   - `Roulette.hpp` / `Roulette.cpp`
   - `main.cpp`

2. **Compile the Code:**  
   Use your favorite C++ compiler. For example, with `g++`:
   ```bash
   g++ -std=c++17 -o RouletteGame main.cpp Player.cpp Casino.cpp Roulette.cpp
