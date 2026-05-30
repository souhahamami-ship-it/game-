#pragma once 
#include "Entity.h"
#include "Inventory.h"
#include <iostream>
#include <string>
using namespace std;
class Player : public Entity {
private: Inventory inventory;
public:
   void   attack(Entity& target) override;
   void   useItem(string name);
   Inventory& getInventory();
   Player(string name, int hp, int maxHp, int atk);
   ~Player();
};
