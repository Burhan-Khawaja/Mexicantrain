#pragma once
#include <iostream>
#include "Tile.h"

Tile::Tile(int firstNum, int secondNum) {
    this->T_firstNumber = firstNum;
    this->T_secondNumber = secondNum;
}

int Tile::getFirstNumber() {
    return this->T_firstNumber;
}

int Tile::getSecondNumber() {
    return this->T_secondNumber;
}

bool Tile::isDouble() {
    if (T_firstNumber == T_secondNumber) {
        return true;
    }
    else {
        return false;
    }
}

void Tile::printTile() {
    std::cout << T_firstNumber << " - " << T_secondNumber;
}

bool Tile::operator==(const Tile& lhs)
{
    // TODO: insert return statement here
    return (this->T_firstNumber == lhs.T_firstNumber && this->T_secondNumber == lhs.T_secondNumber);
}


