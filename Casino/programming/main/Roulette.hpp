#pragma once
#include "Player.hpp"
#include <vector>
#include <string>
#include <utility>

class Roulette
{
public:
    explicit Roulette(const std::vector<Player>& players);
    void Spin();
    std::vector<std::pair<Player, Bet>> PlaceBets();

private:
    std::vector<Player> players_;
    std::vector<std::pair<std::string, unsigned int>> tableNumbers_;
    std::pair<std::string, unsigned int> GetRandomNumber() const;
    void GenerateTable();
};
