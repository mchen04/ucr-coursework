#ifndef INT_VECTOR
#define INT_VECTOR

#include <iostream>

using namespace std;

class IntVector {
  private:
    unsigned _size ;
    unsigned _capacity ;
    int *_data ;
  public: 
    IntVector(unsigned capacity, int value) ;
    ~IntVector() ;
    unsigned size() const ;
    unsigned capacity() const ;
    bool empty() const ;
    const int & at(unsigned index) const ;
    const int & front() const ;
    const int & back() const ;
    void print() ;

};

#endif //INT_VECTOR
