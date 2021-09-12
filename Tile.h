#pragma once

class Tile {
public:
    Tile();
    Tile(int firstNum, int secondNum);
    int getFirstNumber();
    int getSecondNumber();
    bool isDouble();
    void printTile();    
    bool operator==(const Tile& lhs);
    void setValues(int val1, int val2);
protected:

private:
    int T_firstNumber;
    int T_secondNumber;
};