#pragma once 
#include "Room.h"
#include <iostream>
#include <string>
using namespace std;
class Map {
private:
    Room* root;
    Room* rooms[4];
public:
    Map();
    Room* getRoot();
    ~Map();
};