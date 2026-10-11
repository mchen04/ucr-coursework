#include "IntList.h"

#include <ostream>

using namespace std;

IntList::IntList() : head(nullptr) {}

void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

ostream & operator<<(ostream & out, const IntList & rhs){
   IntNode* temp = rhs.head ;
   out << temp ;
   return out ;
}

ostream & operator<<(ostream & out, IntNode* temp){
   if (temp == nullptr){
      return out ;
   }
   if (temp -> next == nullptr){
      out << temp -> value ;
      return out ;
   }
   out << temp -> value << " " ;

   operator<<(out, temp -> next) ;
   return out ; 
}

bool IntList::exists(int num) const{
   IntNode* temp = head ;
   return exists(temp, num) ;
}

bool IntList::exists(IntNode* temp, int num) const{
   if (temp == nullptr) {
      return false ;
   }
   if (temp -> value == num) {
      return true ;
   }
   return exists(temp -> next, num) ;
}

