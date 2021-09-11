#pragma once

class Tile {
public:
    Tile(int firstNum, int secondNum);
    int getFirstNumber();
    int getSecondNumber();
    bool isDouble();
    void printTile();    
    bool operator==(const Tile& lhs);

protected:

private:
    int T_firstNumber;
    int T_secondNumber;
};