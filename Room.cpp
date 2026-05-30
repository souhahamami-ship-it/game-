#include "Room.h"
#include <iostream>
#include <string>
using namespace std;

Room::Room(string name, string description) {
    this->name = name;
    this->description = description;
    this->enemy = nullptr;   // ← set to nullptr
    this->loot = nullptr;    // ← set to nullptr
    north = south = east = west = nullptr;
}
void Room::setNorth(Room* room) {
    north = room;
}
void Room::setSouth(Room* room) {
    south = room;
}
void Room::setEast(Room* room) {
    east = room;
}
void Room::setWest(Room* room) {
    west = room;
}
void Room::setEnemy(Enemy* enemy) {
    this->enemy = enemy;
}
void Room::setLoot(Item* loot) {
    this->loot = loot;
}
string Room::getName() {
    return name;
}
string Room::getDescription() {
    return description;
}
Item* Room::getLoot() {
    return loot;
}
Enemy* Room::getEnemy() {
    return enemy;
}
Room* Room::getNorth() {
    return north;
}
Room* Room::getSouth() {
    return south;
}
Room* Room::getEast() {
    return east;
}
Room* Room::getWest() {
    return west;
}
Room::~Room() {
if (enemy != nullptr) delete enemy;
if (loot != nullptr) delete loot;
}