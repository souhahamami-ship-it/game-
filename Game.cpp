#include "Game.h"
#include <iostream>
using namespace std;
Game::Game() {
    map = new Map();
    player = new Player("Hero", 100, 100, 10);
    currentRoom = map->getRoot();
    gameOver = false;
}
Game::~Game() {
    delete player;
    delete map;
}
void Game::start() {
     cout << "============================" << endl;
    cout << "   Welcome to Dungeon RPG!  " << endl;
    cout << "============================" << endl;
    while (!gameOver) {

        // 1. show current room info
        cout << "You are in: " << currentRoom->getName() << endl;
        cout << currentRoom->getDescription() << endl;
         if (currentRoom->getEnemy() != nullptr) {
            cout << "An enemy is here: " << currentRoom->getEnemy()->getName() << endl;
        }
         if (currentRoom->getLoot() != nullptr) {
            cout << "You see a " << currentRoom->getLoot()->getName() << " on the ground." << endl;
        }
         cout << "Available directions: ";
        // 2. read player input
        cout << "\n> Enter command (go/attack/pickup/inventory/use/quit): ";
        string command;
        cin >> command;

        // 3. if "go north/south/east/west" → move
         if (command == "go") {
            cout << "Enter direction (north/south/east/west): ";
            string direction;
            cin >> direction;
            Room* nextRoom = nullptr;
            if (direction == "north") nextRoom = currentRoom->getNorth();
            else if (direction == "south") nextRoom = currentRoom->getSouth();
            else if (direction == "east") nextRoom = currentRoom->getEast();
            else if (direction == "west") nextRoom = currentRoom->getWest();
            if (nextRoom != nullptr) {
                currentRoom = nextRoom;
            } else {
                cout << "You can't go that way!" << endl;
            }
        }
        // 4. if "attack" → combat
        else if (command == "attack") {
            if (currentRoom->getEnemy() != nullptr) {
        Enemy* enemy = currentRoom->getEnemy();
        player->attack(*enemy);
        if (!enemy->isAlive()) {
            cout << enemy->getName() << " defeated!" << endl;
            currentRoom->setEnemy(nullptr);
        } else {
            enemy->attack(*player);
        }
    } else {
        cout << "No enemy here!" << endl;
    }
        }

        // 5. if "inventory" → show items
        else if (command == "inventory") {
            player->getInventory().displayItems();
        }

        // 6. if "use [item]" → use item
        else if (command == "use") {
    string itemName;
    cin.ignore();                    // ← clears the buffer
    getline(cin, itemName);          // ← reads full name with spaces
    player->useItem(itemName);
}
else if (command == "pickup") {
    if (currentRoom->getLoot() != nullptr) {
        Item* loot = currentRoom->getLoot();
        cout << "You picked up: " << loot->getName() << "!" << endl;
        player->getInventory().addItem(loot);
        currentRoom->setLoot(nullptr);
    } else {
        cout << "Nothing to pick up here!" << endl;
    }
}
        // 7. quit
        else if (command == "quit") {
            cout << "Goodbye!" << endl;
            gameOver = true;
        }

        else {
            cout << "Unknown command!" << endl;
        }
        // 8. check if player is dead
        if (!player->isAlive()) {
            cout << "You have been defeated! Game Over." << endl;
            gameOver = true;
        }
    }
}
