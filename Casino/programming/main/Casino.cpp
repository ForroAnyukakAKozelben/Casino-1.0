#include "Casino.hpp"
#include <stdexcept>
#include <algorithm>

// Initializes the casino with a name and a list of players.
Casino::Casino(const std::string& casinoName, const std::vector<Player>& players) : casinoName_(casinoName), players_(players)
{
}

int Casino::GetNumberOfPlayers() const
{
    return static_cast<int>(players_.size());
}

Player Casino::GetHighestBalancePlayer() const
{
    if (players_.empty()) {
        throw std::runtime_error("No players in the casino");
    }

    auto maxIt = std::max_element(players_.begin(), players_.end(), [](const Player& a, const Player& b) {
        return a.GetBalance() < b.GetBalance();
        });

    return *maxIt;
}

void Casino::AddPlayer(const Player& player)
{
    players_.push_back(player);
}
