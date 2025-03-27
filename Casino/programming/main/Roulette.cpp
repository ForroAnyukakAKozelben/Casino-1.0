#include "Roulette.hpp"
#include "Player.hpp"
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>

// Returns the payout multiplier based on the bet type.
static unsigned int GetBetMultiplier(const Bet& bet) {
    switch (bet.type) {
    case BetType::StraightUp:  return 35;
    case BetType::Split:       return 17;
    case BetType::Street:      return 11;
    case BetType::Corner:      return 8;
    case BetType::Basket:      return 6;
    case BetType::Line:        return 5;
    case BetType::Column:      return 2;
    case BetType::Dozen:       return 2;
    case BetType::EvenOdd:     return 1;
    case BetType::RedBlack:    return 1;
    default:                   return 0;
    }
}

// Evaluates whether the bet wins given the winning tile.
static bool EvaluateBet(const Bet& bet, const std::pair<std::string, unsigned int>& winningTile) {
    unsigned int winNumber = winningTile.second;
    std::string winColor = winningTile.first;

    switch (bet.type) {
    case BetType::StraightUp:
    case BetType::Split:
    case BetType::Street:
    case BetType::Corner:
    case BetType::Basket:
    case BetType::Line:
        return std::find(bet.numbers.begin(), bet.numbers.end(), winNumber) != bet.numbers.end();
    case BetType::Column:
        if (winNumber == 0)
            return false;
        return (((winNumber - 1) % 3) + 1) == std::stoi(bet.option);
    case BetType::Dozen:
        if (winNumber == 0)
            return false;
        return (((winNumber - 1) / 12) + 1) == std::stoi(bet.option);
    case BetType::EvenOdd:
        if (winNumber == 0)
            return false;
        return ((winNumber % 2 == 0) ? "Even" : "Odd") == bet.option;
    case BetType::RedBlack:
        return winColor == bet.option;
    default:
        return false;
    }
}

Roulette::Roulette(const std::vector<Player>& players)
    : players_(players)
{
    GenerateTable();
}

void Roulette::Spin()
{
    if (players_.empty()) {
        std::cout << "No players available." << std::endl;
        return;
    }

    const unsigned int wager = 10;
    std::cout << "Spinning the wheel..." << std::endl;
    auto winningTile = GetRandomNumber();
    std::cout << "Winning number: " << winningTile.second << " (" << winningTile.first << ")" << std::endl;

    for (auto& player : players_)
    {
        Bet bet = player.GetBet();
        if (player.GetBalance() < wager) {
            std::cout << player.GetName() << " does not have enough balance to wager." << std::endl;
            continue;
        }
        player.SetBalance(player.GetBalance() - wager);

        bool win = EvaluateBet(bet, winningTile);
        unsigned int multiplier = GetBetMultiplier(bet);

        if (win) {
            unsigned int winnings = wager * multiplier;
            player.SetBalance(player.GetBalance() + winnings);
            std::cout << player.GetName() << " wins! Bet: ";
        }
        else {
            std::cout << player.GetName() << " loses. Bet: ";
        }

        if (!bet.numbers.empty()) {
            std::cout << "Numbers: ";
            for (auto num : bet.numbers)
                std::cout << num << " ";
        }
        if (!bet.option.empty()) {
            std::cout << "Option: " << bet.option;
        }
        std::cout << ", New Balance: " << player.GetBalance() << std::endl;
    }
}

std::vector<std::pair<Player, Bet>> Roulette::PlaceBets()
{
    std::vector<std::pair<Player, Bet>> betters;
    for (const auto& player : players_) {
        Bet bet = player.GetBet();
        betters.emplace_back(player, bet);
    }
    return betters;
}

std::pair<std::string, unsigned int> Roulette::GetRandomNumber() const
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    std::uniform_int_distribution<unsigned int> dist(0, static_cast<unsigned int>(tableNumbers_.size() - 1));
    unsigned int index = dist(rng);
    return tableNumbers_.at(index);
}

void Roulette::GenerateTable()
{
    tableNumbers_ = {
        { "GREEN", 0 },
        { "RED", 1 },
        { "BLACK", 2 },
        { "RED", 3 },
        { "BLACK", 4 },
        { "RED", 5 },
        { "BLACK", 6 },
        { "RED", 7 },
        { "BLACK", 8 },
        { "RED", 9 },
        { "BLACK", 10 },
        { "BLACK", 11 },
        { "RED", 12 },
        { "BLACK", 13 },
        { "RED", 14 },
        { "BLACK", 15 },
        { "RED", 16 },
        { "BLACK", 17 },
        { "RED", 18 },
        { "RED", 19 },
        { "BLACK", 20 },
        { "RED", 21 },
        { "BLACK", 22 },
        { "RED", 23 },
        { "BLACK", 24 },
        { "RED", 25 },
        { "BLACK", 26 },
        { "RED", 27 },
        { "BLACK", 28 },
        { "BLACK", 29 },
        { "RED", 30 },
        { "BLACK", 31 },
        { "RED", 32 },
        { "BLACK", 33 },
        { "RED", 34 },
        { "BLACK", 35 },
        { "RED", 36 }
    };
}
