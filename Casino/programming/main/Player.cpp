#include "Player.hpp"
#include <utility>

// Constructor.
Player::Player(std::string name, unsigned int balance)
    : name(std::move(name)), balance(balance), bet{ BetType::StraightUp, {0}, "" }
{
}

std::string Player::GetName() const {
    return name;
}

unsigned int Player::GetBalance() const {
    return balance;
}

void Player::SetBalance(unsigned int newBalance) {
    balance = newBalance;
}

// StraightUp bet: one number.
void Player::SetBet(unsigned int newBet) {
    Bet newBetStruct;
    newBetStruct.type = BetType::StraightUp;
    newBetStruct.numbers = { newBet };
    newBetStruct.option.clear();
    bet = newBetStruct;
}

// Split bet: two adjacent numbers.
void Player::SetBet(unsigned int num1, unsigned int num2) {
    Bet newBetStruct;
    newBetStruct.type = BetType::Split;
    newBetStruct.numbers = { num1, num2 };
    newBetStruct.option.clear();
    bet = newBetStruct;
}

// Street bet: three numbers in a row.
void Player::SetBet(unsigned int num1, unsigned int num2, unsigned int num3) {
    Bet newBetStruct;
    newBetStruct.type = BetType::Street;
    newBetStruct.numbers = { num1, num2, num3 };
    newBetStruct.option.clear();
    bet = newBetStruct;
}

// Corner bet: four numbers that form a square.
void Player::SetBet(unsigned int num1, unsigned int num2, unsigned int num3, unsigned int num4) {
    Bet newBetStruct;
    newBetStruct.type = BetType::Corner;
    newBetStruct.numbers = { num1, num2, num3, num4 };
    newBetStruct.option.clear();
    bet = newBetStruct;
}

// Basket bet: fixed bet on {0, "00", 1, 2, 3}. Here we represent "00" as a string option.
void Player::SetBetBasket() {
    Bet newBetStruct;
    newBetStruct.type = BetType::Basket;
    newBetStruct.numbers = { 0, 1, 2, 3 }; // Represent 0,1,2,3 as numbers.
    newBetStruct.option = "00";           // "00" stored in option.
    bet = newBetStruct;
}

// Line bet: six numbers vertically.
void Player::SetBetLine(const std::vector<unsigned int>& numbers) {
    if (numbers.size() != 6) {
        // Optionally handle error here.
        return;
    }
    Bet newBetStruct;
    newBetStruct.type = BetType::Line;
    newBetStruct.numbers = numbers;
    newBetStruct.option.clear();
    bet = newBetStruct;
}

// For Column, Dozen, EvenOdd, or RedBlack bets.
void Player::SetBet(BetType betType, const std::string& option) {
    Bet newBetStruct;
    newBetStruct.type = betType;
    newBetStruct.numbers.clear();
    newBetStruct.option = option;
    bet = newBetStruct;
}

Bet Player::GetBet() const {
    return bet;
}
