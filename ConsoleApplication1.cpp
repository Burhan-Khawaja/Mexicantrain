// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Tile.h"
#include "Hand.h"
#include "Round.h"
#include "Game.h"
#include "Train.h"
#include "Computer.h"
#include "Human.h"

void tileTesting() {
    std::cout << "Creating a new tile, 3-4\n";
    Tile testTile(3, 4);
    std::cout << "Confriming the tile is: ";
    testTile.printTile();
    std::cout << std::endl;

    std::cout << "Creating a double tile, 9-9\n";
    Tile doubleTile(9, 9);
    std::cout << "Confriming the tile is: ";
    doubleTile.printTile();
    if (!doubleTile.isDouble()) {
        std::cout << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ";
        std::cout << "Double tile is not a double for some reason";
    }
    std::cout << std::endl;
}

void handTesting() {
    Hand testHand;
    for (int i = 0; i < 5; i++) {
        testHand.addTile(Tile(i, i));
    }
    testHand.printHand();
    Tile testTile(1, 1);
    Tile testTile2(0, 0);    
    Tile testTile3(0, 0);

    if (testTile == testTile2) {
        std::cout << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ";
    }
    if ( testTile2 == testTile3) {
        //do nothing if they match since thats whats supposed to happen.
        //hvaent overloaded '!' operator yet since im lazy. get to that. jeez.
    }
    else {
        std::cout << "ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ";
    }
    //0,0 and 4,4 tile are present in hand but not 9,9
    testHand.removeTile(9, 9);
    testHand.removeTile(0, 0);
    testHand.removeTile(4, 4);
}

void roundTesting() {
    Round roundTest;
    //roundTest.instantiateDeck();
    //roundTest.shuffleDeck();
    //roundTest.dealTiles();
    roundTest.startRound();
}

void gameTesting() {
    Game gameTest;
    for (int i = 0; i < 20; i++) {
        int engineValue = gameTest.getNextEngineValue();
        std::cout << engineValue << ", ";
    }
}

void trainTesting() {
    Train testTrain;    
    for (int i = 0; i < 5; i++) {
        testTrain.addTileFront(Tile(i, i));
    }
    testTrain.printTrain();

    //orphan double function testing
    testTrain.setOrphanDouble();//sets orphan double to true
    if (testTrain.getOrphanDouble() == false) {
        std::cout << "ERROPR ERRORERROR THIS STATEMENT HSOULD NOT EXECUTE.";
    }
    testTrain.resetOrphanDouble();
    if (testTrain.getOrphanDouble() == false) {
        std::cout << "\nThe train's orphan boolean has been reset.";
    }
}

void playerTesting() {
    Human* humanTest;
    Computer* computerTest;
    humanTest = new Human;
    computerTest = new Computer;
    Tile testTile(3, 4);
    humanTest->addTileToHand(testTile);
    computerTest->addTileToHand(testTile);

}

int main()
{
    std::cout << "Welcome to Mexican Train!\n";
    //tileTesting(); 
    //handTesting();
    roundTesting();
    //gameTesting();
    //trainTesting(); 
    //playerTesting();
}


