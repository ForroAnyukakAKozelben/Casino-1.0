#pragma once
#include "Player.hpp"
#include <vector>
#include <string>
#include <stdexcept>

class Casino
{
public:
    // Constructor: Initializes the casino with a name and a list of players.
    explicit Casino(const std::string& casinoName, const std::vector<Player>& players);

    // Returns the number of players.
    int GetNumberOfPlayers() const;

    // Returns the player with the highest balance.
    // Throws an exception if there are no players.
    Player GetHighestBalancePlayer() const;

    // Adds a new player to the casino.
    void AddPlayer(const Player& player);

private:
    std::vector<Player> players_;
    std::string casinoName_;
};
