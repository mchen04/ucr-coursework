#include <iostream>
using namespace std;

#include "Character.h"
#include "Warrior.h"

Warrior::Warrior(const string& name, double health, double strength, string allegiance) :
    Character(HeroType::WARRIOR, name, health, strength), allegiance(allegiance) {}

void Warrior::attack(Character &opponent) { 
    if (opponent.getType() == type){
        Warrior &opp = dynamic_cast<Warrior &>(opponent);
        if (opp.getAllegiance() ==  allegiance){
            cout << "Warrior " << name << " does not attack Warrior " << opp.getName() << "." << endl ;
            cout << "They share an allegiance with " << allegiance << "." << endl ;
            return ;
        }
    }
    opponent.damage( ( health / MAX_HEALTH) * (attackStrength)) ;
    cout << "Warrior " << name << " attacks " << opponent.getName() << " --- SLASH!!" << endl ;
    cout << opponent.getName() << " takes " << (health / MAX_HEALTH) * (attackStrength) << " damage." << endl ;
}

string Warrior::getAllegiance() const {
    return allegiance ;
}