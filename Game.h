#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <fstream>
#include "Round.h"


class Game {
public:
    int getRoundNumber();
    void setRoundNumber(int roundNum);
    int getHumanScore();
    void setHumanScore(int hScore);
    int getComputerScore();
    void setComputerScore(int cScore);
    void resetEngineQueue();
    int getNextEngineValue();
    void playGame();
    void addComputerScore(int pipVal);
    void addHumanScore(int pipVal);
    void playAgainPrompt();
    void outputWinner();
    void loadGame();
    void setHand(std::deque<Tile> tiles, int whoseHand);
    void saveGame();
    std::deque<Tile> parseLineOfTiles(std::string input, bool& setMarker);
protected:
private:
    int roundNumber;
    int humanScore;
    int computerScore;
    Round round;
    std::deque<int> engineQueue;
};