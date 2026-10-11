#ifndef WIZARD__
#define WIZARD__

#include "Character.h"

using namespace std;

class Wizard : public Character {
    public: 
        Wizard(const string &, double, double, int );   
        void attack(Character &) override ;
        int getRank() const ;
    private: 
        int rank ;  
};

#endif