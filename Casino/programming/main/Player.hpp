#pragma once
#include <string>
#include <vector>

enum class BetType {
    StraightUp,  // 35:1
    Split,       // 17:1
    Street,      // 11:1
    Corner,      // 8:1
    Basket,      // 6:1 (American Roulette only)
    Line,        // 5:1
    Column,      // 2:1
    Dozen,       // 2:1
    EvenOdd,     // 1:1
    RedBlack     // 1:1
};

struct Bet {
    BetType type;
    std::vector<unsigned int> numbers; // For bets based on numbers.
    std::string option;                // For Column, Dozen, EvenOdd, or RedBlack bets.
};

class Player
{
public:
    Player(std::string name, unsigned int balance);
    std::string GetName() const;
    unsigned int GetBalance() const;
    void SetBalance(unsigned int balance);

    // Overloads for setting bets.
    // StraightUp bet.
    void SetBet(unsigned int newBet);
    // Split bet (two numbers).
    void SetBet(unsigned int num1, unsigned int num2);
    // Street bet (three numbers).
    void SetBet(unsigned int num1, unsigned int num2, unsigned int num3);
    // Corner bet (four numbers).
    void SetBet(unsigned int num1, unsigned int num2, unsigned int num3, unsigned int num4);
    // Basket bet (fixed: 0, "00", 1, 2, 3; note: "00" is represented as a special string in option).
    void SetBetBasket();
    // Line bet (six numbers).
    void SetBetLine(const std::vector<unsigned int>& numbers);
    // For bets where only an option is needed (Column, Dozen, EvenOdd, RedBlack).
    void SetBet(BetType betType, const std::string& option);

    Bet GetBet() const;

private:
    std::string name;
    unsigned int balance;
    Bet bet;
};
