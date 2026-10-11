#include <iostream> 
#include "Distance.h"
using namespace std ;

Distance::Distance(){
    feet = 0 ;
    inches = 0.0 ;
}

Distance::Distance(unsigned ft, double in){
    feet = ft ;
    inches = in ;
    init () ;
}

Distance::Distance(double in){
    feet = 0 ;
    inches = in ;
    init () ;
}

unsigned Distance::getFeet() const{
    return feet ;
}

double Distance::getInches() const{
    return inches ;
}

double Distance::distanceInInches() const{
    return ( (feet * 12) + inches ) ;
}

double Distance::distanceInFeet() const{
    return ( feet + (inches / 12)) ;
}

double Distance::distanceInMeters() const{
    return ( (feet * 12 + inches) * 0.0254) ;
}

Distance Distance::operator+(const Distance &rhs) const{
    Distance Distance ;
    Distance.feet = this->feet + rhs.feet ;
    Distance.inches = this->inches + rhs.inches ;

    if ( Distance.inches >= 12 ){
        Distance.feet += 1 ;
        Distance.inches -= 12 ;
    }

    return Distance ;
}

Distance Distance::operator-(const Distance &rhs) const{
    Distance Distance ;

    if ( this->feet < rhs.feet ){
        Distance.feet = rhs.feet - this->feet ;
        Distance.inches = rhs.inches - this->inches;
    }
    else{
        Distance.feet = this->feet - rhs.feet ;
        Distance.inches = this->inches - rhs.inches;
    }

    if ( Distance.inches < 0 ){
        Distance.feet -= 1 ;
        Distance.inches += 12.0 ;
    }

    return Distance ;
}

ostream & operator<<(ostream &out, const Distance &rhs){
    out << rhs.feet << "' "<< rhs.inches << "\"" ;
    return out ;
}

void Distance::init(){
    int ft = feet ;
    double in = abs(inches) ;

    if( inches < 0) {
        inches *= -1 ;
    } 

    if ( in >= 12 ){
        feet = ft + (in / 12.0) ;
        inches = in - ((feet - ft) * 12) ;
    }
}
