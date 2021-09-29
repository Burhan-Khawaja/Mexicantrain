#pragma once
#include <iostream>
#include <deque>
#include <vector>
#include <sstream>
#include <fstream>
#include "Round.h"


class Game {
public:
    Game();

    int const getHumanScore();

    int getComputerScore();

    int const getRoundNumber();

    void setRoundNumber(int roundNum);

    void setHand(std::deque<Tile> tiles, int whoseHand);

    void setHumanScore(int hScore);

    void setComputerScore(int cScore);

    void playGame();

    void addComputerScore(int pipVal);

    void addHumanScore(int pipVal);

    void playAgainPrompt();

    void outputWinner();

    void loadGame();   

    void saveGame();

    std::deque<Tile> parseLineOfTiles(std::string input, bool& setMarker);

    void printDequeToFile(std::ofstream& file, std::deque<Tile>& tiles);

protected:
private:
    //stores the current round number
    int roundNumber;
    //stores the human score
    int humanScore;
    //stores the computer score
    int computerScore;
    //round object that stores all the information required to play a round (human/player objects, mexican train, boneyard, etc)
    Round round;
    //deque that stores the values of the engine unit for every round ( 9-0 in descending order).
    std::deque<int> engineQueue;
};