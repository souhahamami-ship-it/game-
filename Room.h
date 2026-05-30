#pragma once 
#include <iostream>
#include <string>
#include "Enemy.h"
#include "Item.h"
using namespace std;
class Room {
private:
   string name;
   string description;
   Enemy* enemy;
   Item* loot;
   Room* north;
   Room* south;
   Room* east;
   Room* west;
public:
   Room(string name, string description);  
    void setNorth(Room* room);
    void setSouth(Room* room);
    void setEast(Room* room);
    void setWest(Room* room);
    void setEnemy(Enemy* enemy);
    void setLoot(Item* loot);
    string getName();
    string getDescription();
    Item* getLoot();
    Enemy* getEnemy();
    Room* getNorth();
    Room* getSouth();
    Room* getEast();
    Room* getWest();
    ~Room();
    
    
};
