#include <iostream>
using namespace std;

#include "Character.h"
#include "Elf.h"

Elf::Elf(const string& name, double health, double strength, string family) :
    Character(HeroType::ELF, name, health, strength), family(family) {}

void Elf::attack(Character &opponent) { 

    if (opponent.getType() == type){
        Elf &opp = dynamic_cast<Elf &>(opponent);
        if (opp.getFamily() == family){
            cout << "Elf " << name << " does not attack Elf " << opp.getName() << "." << endl ;
            cout << "They are both members of the " << family << " family." << endl ;
            return ;
        }
    }
    opponent.damage( (health / MAX_HEALTH) * (attackStrength)) ;
    cout << "Elf " << name << " shoots an arrow at " << opponent.getName() << " --- TWANG!!" << endl ;
    cout << opponent.getName() << " takes " << (health / MAX_HEALTH) * (attackStrength) << " damage." << endl ;

}

string Elf::getFamily() const {
    return family ;
}