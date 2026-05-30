
#include <iostream>
#include <string>
#include "Item.h"
#include "Inventory.h"

Inventory::Inventory() {
    head = nullptr;
}
void Inventory::addItem(Item* i){
    Node* newnode=new Node;
    newnode->item=i;
    newnode->next=nullptr;
    if (head == nullptr) {
        head = newnode;
        return;
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newnode;
}




void Inventory::removeItem(string itemName) {
    Node* current = head;
    Node* previous = nullptr;
    while (current != nullptr) {
        if (current->item->getName() == itemName) {
            if (previous == nullptr) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            delete current->item;
            delete current;
            return;
        }
        previous = current;
        current = current->next;
    }
}
void Inventory::displayItems() {
    Node* current = head;
    while (current != nullptr) {
        cout << current->item->getName() << " (Heal: " << current->item->getHealAmount() 
             << ", ATK Bonus: " << current->item->getAtkBonus() << ")" << endl;
        current = current->next;
    }
}
Node* Inventory::getHead() {
    return head;
}
Inventory::~Inventory() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp->item; // Assuming Inventory owns the Items
        delete temp;
    }
}

