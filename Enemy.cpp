#include "Entity.h"
#include "Enemy.h"
#include <iostream>
#include <string>
using namespace std;

Enemy::Enemy(string name, int hp, int maxHp, int atk) : 
Entity(name, hp, maxHp, atk) {}

void Enemy::attack(Entity& target) {
   cout << name << " attacks you for " << atk << " damage!";
    target.takeDamage(atk);
}
Enemy::~Enemy() {}