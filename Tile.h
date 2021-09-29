#pragma once

class Tile {
public:
    Tile();

    Tile(int firstNum, int secondNum);
    int const getFirstNumber() ;
    int const getSecondNumber();
    bool isDouble();
    void printTile();    
    bool const operator==(const Tile& lhs);
    void swapNumbers();
protected:

private:
    //T_firstNumber and T_secondNumber will store the tile's numbers.
    //(ie a tile of 4-6 will have 4 be stored in T_firstNumber, and 6 in T_secondNumber) 
    int T_firstNumber;
    int T_secondNumber;
};