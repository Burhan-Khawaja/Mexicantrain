#include "Game.h"

int Game::getRoundNumber() {
    return 0;
}

int Game::getHumanScore() {
    return 0;
}

int Game::getComputerScore() {
    return 0;
}

void Game::resetEngineQueue() {
    engineQueue.clear();
    for (int i = 0; i < 10; i++) {
        engineQueue.push_front(i);
    }
}

int Game::getNextEngineValue() {
    if (engineQueue.empty()) {
        resetEngineQueue();
    }
    int tmpVal = engineQueue.front();
    engineQueue.pop_front();
    return tmpVal;
}

void Game::playGame() {
    int pipValue = round.startRound();//start round returns pip value.
    //have to call getWinner function to find ouit which player won.
    if (round.getWinner()) {
        addComputerScore(pipValue);
    }
    else {
        addHumanScore(pipValue);
    }
    playAgainPrompt();
}

void Game::addComputerScore(int pipVal)
{
    this->computerScore += pipVal;
}

void Game::addHumanScore(int pipVal)
{
    this->humanScore += pipVal;
}

void Game::playAgainPrompt()
{
    char userInput;
    do {
        std::cout << "\n\n\n Would you like to play again? (y/Y/n/N)";
        std::cin >> userInput;
        userInput = tolower(userInput);
        if (userInput != 'y' && userInput != 'n') {
            std::cout << "\n\nInvalid input try again.\n\n";
        }
    } while (userInput != 'y' && userInput != 'n');
    if (userInput == 'y') {
        playGame();
    }
    else if (userInput == 'n') {
        outputWinner();
    }
}

void Game::outputWinner()
{
    std::cout << "Your score: ";
    getHumanScore();
    std::cout << "\nComputer Score: ";
    getComputerScore();
    if (getHumanScore() == getComputerScore()) {
        std::cout << "\nThe game is a tie!";
    }
    else if (getHumanScore() > getComputerScore()) {
        std::cout << "\nYou won the game! congratulations";
    }
    else {
        std::cout << "You lost.";
    }
}
