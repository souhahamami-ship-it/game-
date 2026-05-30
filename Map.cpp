#include "Map.h"
#include <iostream>
#include <string>
using namespace std;
Map::Map() {
    // Create rooms
    Room* cave       = new Room("Cave Entrance", "A dark and damp cave. You smell danger.");
    Room* darkHall   = new Room("Dark Hall", "Torches flicker on the stone walls.");
    Room* treasure   = new Room("Treasure Room", "Gold coins scatter across the floor.");
    Room* boss       = new Room("Boss Chamber", "The ground shakes. A Dragon rises!");
    // Store rooms in array for easy access
    rooms[0] = cave;
    rooms[1] = darkHall;
    rooms[2] = treasure;
    rooms[3] = boss;
    // Connect rooms
    cave->setNorth(darkHall);
    darkHall->setSouth(cave);
    cave->setEast(treasure);
    treasure->setWest(cave);
    darkHall->setNorth(boss);
    boss->setSouth(darkHall);
    // Set root to the starting room
   root = cave;

    // add enemies
    darkHall->setEnemy(new Enemy("Goblin", 30, 30, 8));
    boss->setEnemy(new Enemy("Dragon", 120, 120, 25));

    // add loot
    cave->setLoot(new Item("Health Potion", 30, 0));
    treasure->setLoot(new Item("Magic Sword", 0, 10));
}
Room* Map::getRoot() {
    return root;
}
Map::~Map() {
    for (int i = 0; i < 4; i++) {
        delete rooms[i];
    }
}