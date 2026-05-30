#pragma once
#include "Map.h"
#include "Player.h"
#include "Room.h"
#include <iostream>
using namespace std;

class Game {
private:
    Map* map;
    Player* player;
    Room* currentRoom;
    bool gameOver;
public:
    Game();
    void start();
    ~Game();
};