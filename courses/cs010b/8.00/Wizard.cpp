#include <iostream>
using namespace std;

#include "Character.h"
#include "Wizard.h"

Wizard::Wizard(const string& name, double health, double strength, int rank) :
    Character(HeroType::WIZARD, name, health, strength), rank(rank) {}

void Wizard::attack(Character &opponent) { 
    if (opponent.getType() == type){
        Wizard &opp = dynamic_cast<Wizard &>(opponent);
        opp.damage( ( static_cast<double>(rank) / static_cast<double>(opp.getRank())) * ( attackStrength)) ;
        cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl ;
        cout << opponent.getName() << " takes " << ( static_cast<double>(rank) / static_cast<double>(opp.getRank())) * ( attackStrength) << " damage." << endl ;
        return ;
    }
    opponent.damage( attackStrength ) ;
    cout << "Wizard " << name << " attacks " << opponent.getName() << " --- POOF!!" << endl ;
        cout << opponent.getName() << " takes " << ( attackStrength) << " damage." << endl ;
}

int Wizard::getRank() const {
    return rank ;
}