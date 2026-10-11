#ifndef WARRIOR__
#define WARRIOR__

#include "Character.h"

using namespace std;

class Warrior : public Character {
    public: 
        Warrior(const string &, double, double, string);   
        void attack(Character &) override;
        string getAllegiance() const ;
    private: 
        string allegiance ;  
};

#endif