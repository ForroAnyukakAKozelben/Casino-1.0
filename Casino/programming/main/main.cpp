#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include "Player.hpp"
#include "Casino.hpp"
#include "Roulette.hpp"

int main() {
    int numPlayers;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    unsigned int avgCoins;
    std::cout << "Enter the average starting coins for each player: ";
    std::cin >> avgCoins;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<unsigned int> coinDist(avgCoins / 2, (avgCoins * 3) / 2);
    std::uniform_int_distribution<unsigned int> numberDist(0, 36);

    // Create players with varied starting coins.
    std::vector<Player> players;
    for (int i = 0; i < numPlayers; i++) {
        unsigned int coins = coinDist(rng);
        std::string name = "Player " + std::to_string(i + 1);
        players.emplace_back(name, coins);
    }

    auto assignRandomBet = [&rng, &numberDist](Player& p) {
        std::uniform_int_distribution<int> betTypeDist(0, 9); // 10 bet types.
        int betType = betTypeDist(rng);
        switch (betType) {
        case 0: { // StraightUp bet.
            unsigned int num = numberDist(rng);
            p.SetBet(num);
            break;
        }
        case 1: { // Split bet: pick a number from 0 to 35 and use the next one.
            std::uniform_int_distribution<unsigned int> baseDist(0, 35);
            unsigned int num = baseDist(rng);
            p.SetBet(num, num + 1);
            break;
        }
        case 2: { // Street bet: three numbers in a row.
            std::uniform_int_distribution<int> rowDist(0, 11);
            int row = rowDist(rng);
            unsigned int n1 = static_cast<unsigned int>(row * 3 + 1);
            unsigned int n2 = static_cast<unsigned int>(row * 3 + 2);
            unsigned int n3 = static_cast<unsigned int>(row * 3 + 3);
            p.SetBet(n1, n2, n3);
            break;
        }
        case 3: { // Corner bet: four numbers forming a square.
            std::uniform_int_distribution<int> rowDist(0, 10);
            std::uniform_int_distribution<int> colDist(0, 1);
            int row = rowDist(rng);
            int col = colDist(rng);
            unsigned int n1 = static_cast<unsigned int>(row * 3 + col + 1);
            unsigned int n2 = static_cast<unsigned int>(row * 3 + col + 2);
            unsigned int n3 = static_cast<unsigned int>((row + 1) * 3 + col + 1);
            unsigned int n4 = static_cast<unsigned int>((row + 1) * 3 + col + 2);
            p.SetBet(n1, n2, n3, n4);
            break;
        }
        case 4: { // Basket bet.
            p.SetBetBasket();
            break;
        }
        case 5: { // Line bet: six numbers covering two consecutive rows.
            std::uniform_int_distribution<int> rowDist(0, 10);
            int row = rowDist(rng);
            std::vector<unsigned int> nums = {
                static_cast<unsigned int>(row * 3 + 1),
                static_cast<unsigned int>(row * 3 + 2),
                static_cast<unsigned int>(row * 3 + 3),
                static_cast<unsigned int>((row + 1) * 3 + 1),
                static_cast<unsigned int>((row + 1) * 3 + 2),
                static_cast<unsigned int>((row + 1) * 3 + 3)
            };
            p.SetBetLine(nums);
            break;
        }
        case 6: { // Column bet.
            std::uniform_int_distribution<int> colOpt(1, 3);
            int col = colOpt(rng);
            p.SetBet(BetType::Column, std::to_string(col));
            break;
        }
        case 7: { // Dozen bet.
            std::uniform_int_distribution<int> dozenOpt(1, 3);
            int d = dozenOpt(rng);
            p.SetBet(BetType::Dozen, std::to_string(d));
            break;
        }
        case 8: { // EvenOdd bet.
            std::uniform_int_distribution<int> eoDist(0, 1);
            int eo = eoDist(rng);
            std::string option = (eo == 0 ? "Even" : "Odd");
            p.SetBet(BetType::EvenOdd, option);
            break;
        }
        case 9: { // RedBlack bet.
            std::uniform_int_distribution<int> rbDist(0, 1);
            int rb = rbDist(rng);
            std::string option = (rb == 0 ? "RED" : "BLACK");
            p.SetBet(BetType::RedBlack, option);
            break;
        }
        default:
            p.SetBet(numberDist(rng));
            break;
        }
        };

    // Assign initial bets.
    for (auto& p : players) {
        assignRandomBet(p);
    }

    Casino casino("Lucky Star", players);
    std::cout << "\nCasino: Lucky Star" << std::endl;
    std::cout << "Number of players: " << numPlayers << std::endl;

    // Game loop: continues until only one player has a positive balance.
    while (true) {
        int activeCount = 0;
        for (const auto& p : players) {
            if (p.GetBalance() > 0)
                activeCount++;
        }
        if (activeCount <= 1)
            break;

        std::cout << "\n---------------------------" << std::endl;
        std::cout << "New turn" << std::endl;

        // Update bets for each active player.
        for (auto& p : players) {
            if (p.GetBalance() > 0)
                assignRandomBet(p);
        }

        Roulette roulette(players);
        roulette.Spin();

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    std::cout << "\nGame over. Final balances:" << std::endl;
    for (const auto& p : players) {
        std::cout << p.GetName() << ": " << p.GetBalance() << std::endl;
    }
    return 0;
}
