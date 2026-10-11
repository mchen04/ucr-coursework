#include <iostream>
using namespace std;

#include "IntList.h"
#include "SortedSet.h"

int main() {

  //tests constructor, destructor, push_front, pop_front, display

   {
      cout << "\nlist1 constructor called" << endl;
      SortedSet set1;
      cout << set1.in(5)  << endl ;
      set1.add(54) ;
      set1.push_front(10) ;
      set1.push_back (12) ;
      set1.insert_ordered(65) ;
      SortedSet set2 ;
      set1 | set2 ;

   }
}
