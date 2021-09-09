#pragma once
#include <iostream>
#include <deque>

class Game {
public:
    int getRoundNumber();
    int getHumanScore();
    int getComputerScore();
    void resetEngineQueue();
    int getNextEngineValue();
    void startGame();
protected:
private:
    int m_roundNumber;
    int m_humanScore;
    int m_computerScore;
    std::deque<int> engineQueue;
};