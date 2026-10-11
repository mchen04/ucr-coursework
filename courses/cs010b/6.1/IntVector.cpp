#include "IntVector.h"

#include <stdexcept>
#include <iomanip> 

IntVector::IntVector(unsigned capacity, int value){
    _size = capacity ;
    _capacity = capacity ;

    _data = new int[_size] ;
        
    for (unsigned i = 0; i < _size; i++) {
        _data[i] = value ;
    }
}

IntVector::~IntVector(){
    cout << "Destuctor Called." << endl ;
    delete _data ;
}

unsigned IntVector::size() const {
    return _size ;
}

unsigned IntVector::capacity() const {
    return _capacity ;
}

bool IntVector::empty() const {
    if (_size == 0){
        return true ;
    }
    else{
        return false ;
    }
}

const int & IntVector::at(unsigned index) const {
    if (index >= _size){
        throw out_of_range("IntVector::at_range_check");
    } 
    return _data[index] ;
}

const int & IntVector::front() const {
    return _data[0] ;
}

const int & IntVector::back() const {
    return _data[_size - 1] ;
}

void IntVector::print() {
    for (unsigned i = 0; i < _size; i++) {
        cout << _data[i] << " ";
    }
    cout << endl;
}
