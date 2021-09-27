#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Hand {
public:
    Hand();
    void addTile(Tile tileToAdd);
    void removeTile(int tileToRemove);
    void removeTile(int index1, int index2);
    void printHand();
    Tile getTile(int);
    int const getSize();
    Tile& operator[](int index);
    void clearHand();
    const std::vector<Tile> getHand();

protected:
private:
    std::vector<Tile> m_hand;
};