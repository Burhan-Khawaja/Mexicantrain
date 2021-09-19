#pragma once
#include <iostream>
#include <deque>
#include "Round.h"
class Game {
public:
    int getRoundNumber();
    int getHumanScore();
    int getComputerScore();
    void resetEngineQueue();
    int getNextEngineValue();
    void playGame();
    void addComputerScore(int pipVal);
    void addHumanScore(int pipVal);
    void playAgainPrompt();
    void outputWinner();
protected:
private:
    int m_roundNumber;
    int humanScore;
    int computerScore;
    Round round;
    std::deque<int> engineQueue;
};