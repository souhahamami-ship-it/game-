#pragma once 
#include "Entity.h"
#include <iostream>
#include <string>
using namespace std;


class Enemy : public Entity {
private:

public:
    Enemy(string name, int hp, int maxHp, int atk);
    void attack(Entity& target) override;
    ~Enemy() override;
};


