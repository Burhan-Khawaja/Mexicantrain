#include "Hand.h"
#include <iostream>
#include <algorithm>

void Hand::addTile(Tile tileToAdd) {
    m_hand.push_back(tileToAdd);
}

void Hand::removeTile(int tileToRemove) {
    m_hand.erase(m_hand.begin() + tileToRemove);
}

//BURBUR need to do error checking and do something if the tile to remove is not in the hand.
void Hand::removeTile(int value1, int value2) {
    Tile tmpTile = Tile(value1, value2);
    std::vector<Tile>::iterator iteratorPos = std::find(m_hand.begin(), m_hand.end(), tmpTile);
    m_hand.erase(std::remove(m_hand.begin(), m_hand.end(), tmpTile), m_hand.end());
}

void Hand::printHand() {
    for (int i = 0; i < m_hand.size(); i++) {
        m_hand[i].printTile();
        std::cout << ", ";
        if (i % 6 == 0 && i > 0) {
            std::cout << std::endl;
        }
    }
}
int Hand::getSize() {
    return m_hand.size();
}

//get Tile by position in array
Tile Hand::getTile(int index) {
    return m_hand[index];
}

Tile& Hand::operator[](int index) {
   // if (index > m_hand.size()) {}
    return m_hand.at(index);
}
