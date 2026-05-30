#include <iostream>
#include <string>
#include "Player.h"
Player::Player(string name, int hp, int maxHp, int atk) : 
          Entity(name, hp, maxHp, atk) {}


void Player::attack(Entity& target) {
    cout << "You attack " << target.getName() << " for " << atk << " damage!" << endl;
    target.takeDamage(atk);
}
Player::~Player() {}
void Player::useItem(string name) {
    Node* current = inventory.getHead();
    while (current != nullptr) {
        if (current->item->getName() == name) {
            hp += current->item->getHealAmount();
            if (hp > maxHp) {
                hp = maxHp;
            }
            atk += current->item->getAtkBonus();
            inventory.removeItem(name);
            cout << "You used " << name << "!" << endl;
            return;
        }
        current = current->next;
    }
    cout << "Item not found in inventory!" << endl;
}
Inventory& Player::getInventory() {
    return inventory;
}