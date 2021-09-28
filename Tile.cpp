#pragma once
#include <iostream>
#include "Tile.h"


Tile::Tile()
{
    //default constructor, set values to -1 so we know they arent valid values.
    this->T_firstNumber = -1;
    this->T_secondNumber = -1;
}



Tile::Tile(int firstNum, int secondNum) {
    //partmentalized constructor. set first and second numbers to the integers passed in.
    this->T_firstNumber = firstNum;
    this->T_secondNumber = secondNum;
}

int const Tile::getFirstNumber()  {
    return this->T_firstNumber;
}

int const Tile::getSecondNumber() {
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

bool const Tile::operator==(const Tile& lhs)
{
    return (this->T_firstNumber == lhs.T_firstNumber && this->T_secondNumber == lhs.T_secondNumber);
}

void Tile::swapNumbers()
{
    int tmp = this->getFirstNumber();
    this->T_firstNumber = this->getSecondNumber();
    this->T_secondNumber = tmp;
}


