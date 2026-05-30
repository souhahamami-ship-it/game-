#pragma once 
#include <iostream>
#include <string>
#include "Item.h"
using namespace std;

struct Node {
    Item* item;   // pointer to an Item
    Node* next;   // pointer to next node
};

class Inventory {
private:
    Node* head;   // pointer to the head of the linked list
public:
    Inventory() ;
    void addItem(Item* newItem) ; 
    void displayItems();
    void removeItem(string itemName) ;
    Node* getHead();
    ~Inventory() ;
};