#pragma once
#include <iostream>
#include "Tile.h"

/* *********************************************************************
Function Name: Tile
Purpose: Set default values of Tile member variables.
Parameters: None
Return Value: None
Assistance Received: None.
********************************************************************* */
Tile::Tile()
{
    this->T_firstNumber = -1;
    this->T_secondNumber = -1;
}

/* *********************************************************************
Function Name: Tile
Purpose: Partmentalized constructor for tile object .
Parameters:
    firstNum - integer passed by value. It is 1 of 2 numbers we want the tile to represent.
    secondNum - integer passed by value. It is the second number we want the tile to have.
Return Value: None
Assistance Received: None
********************************************************************* */
Tile::Tile(int firstNum, int secondNum) {
    this->T_firstNumber = firstNum;
    this->T_secondNumber = secondNum;
}

/* *********************************************************************
Function Name: getFirstNumber.
Purpose: get the first number of the tile.
Parameters: None.
Return Value: The first number of the tile, an integer
Assistance Received: None
********************************************************************* */
int const Tile::getFirstNumber() {
    return this->T_firstNumber;
}

/* *********************************************************************
Function Name: getSecondNumber.
Purpose: get the second number of the tile.
Parameters: None.
Return Value: The second number of the tile, an integer
Assistance Received: None
********************************************************************* */
int const Tile::getSecondNumber() {
    return this->T_secondNumber;
}

/* *********************************************************************
Function Name: isDouble.
Purpose: checks if a  tile is a double.
Parameters: None.
Return Value: True if tile is a double, false if it is not
Algorithm: If the first number and second number of the tile are the same, return true. Else return false.
Assistance Received: None
********************************************************************* */
bool Tile::isDouble() {
    if (T_firstNumber == T_secondNumber) {
        return true;
    }
    else {
        return false;
    }
}

/* *********************************************************************
Function Name: printTile.
Purpose: Print out Tile objects contents to the console.
Parameters: None.
Return Value: None
Assistance Received: None
********************************************************************* */
void Tile::printTile() {
    std::cout << T_firstNumber << " - " << T_secondNumber;
}

/* *********************************************************************
Function Name: operator==.
Purpose: Overload equlaity operator so we can comapre objects of Tile class
Parameters: lhs, which is a const Tile object. This will be the Tile we compare against
Return Value: Bool, true if the tiles have the same first and second number, false if they do not
Assistance Received: None
********************************************************************* */
bool const Tile::operator==(const Tile& lhs)
{
    return (this->T_firstNumber == lhs.T_firstNumber && this->T_secondNumber == lhs.T_secondNumber);
}

/* *********************************************************************
Function Name: swapNumbers.
Purpose: Swap the 2 numbers of a tile. (ie - tile x-y turns into tile y-x)
Parameters: None
Return Value: None
Algorithm: 1) store the Tile's first number in a temporary variable
           2) store the Tile's second number into the tiles first number
           3) store the temporary variable from step 1 into the tiles second variable.
Assistance Received: None
********************************************************************* */
void Tile::swapNumbers()
{
    int tmp = this->getFirstNumber();
    this->T_firstNumber = this->getSecondNumber();
    this->T_secondNumber = tmp;
}


