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

void startGame() {

}
