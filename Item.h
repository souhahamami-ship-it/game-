#pragma once 
#include <iostream>
#include <string>
using namespace std;
class Item {
private:
    string name;
    int healAmount;
    int atkBonus;
public:
    Item(string name, int healAmount, int atkBonus){
        this->name = name;
        this->healAmount = healAmount;
        this->atkBonus = atkBonus;
    }
    string getName() {
        return name;
    }
    int getHealAmount() {
        return healAmount;
    }
    int getAtkBonus() {
        return atkBonus;
    }
    ~Item(){}
};