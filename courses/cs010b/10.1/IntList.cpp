#include "IntList.h"

/* Initializes an empty list.
*/
IntList::IntList() : head(nullptr) {}

/* Inserts a data value to the front of the list.
*/
void IntList::push_front(int val) {
   if (!head) {
      head = new IntNode(val);
   } 
   else {
      IntNode *temp = new IntNode(val);
      temp->next = head;
      head = temp;
   }
}

void IntList::swapHeadAndTail() {
   if (head == nullptr || head -> next == nullptr){
      return ;
   }

   else{
      IntNode* temp = head ;

      while ( temp -> next -> next != nullptr) {
         temp = temp -> next ;
      }

      temp -> next -> next = head ;
      head = temp -> next ;
      temp -> next = head -> next ;
      head -> next = head -> next -> next ;
      temp = head -> next -> next ;

      while ( temp -> next != head -> next){
         temp = temp -> next ;
      } 
      temp -> next = nullptr ;
   }
}
