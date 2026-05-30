#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity(string name, int hp, int maxHp, int atk) {
    this->name  = name;
    this->hp    = hp;
    this->maxHp = maxHp;
    this->atk   = atk;
}

string Entity::getName()     { return name; }
int    Entity::getHp()       { return hp; }
int    Entity::getAtk()      { return atk; }
bool   Entity::isAlive()     { return hp > 0; }

void Entity::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

Entity::~Entity() {}