#pragma once
#include <string>
using namespace std;

class Entity {
protected:
    string name;
    int hp;
    int maxHp;
    int atk;
public:
    Entity(string name, int hp, int maxHp, int atk);
    string getName();
    int getHp();
    int getAtk();
    bool isAlive();
    void takeDamage(int damage);
    virtual void attack(Entity& target) = 0;
    virtual ~Entity();
};