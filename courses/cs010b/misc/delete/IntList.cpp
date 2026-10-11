#include "IntList.h"

#include <iostream>
using namespace std;

IntList::IntList() {
    head = nullptr ;
    tail = nullptr ;
}

IntList::~IntList(){

    IntNode *currVal = head ;

    while (currVal != nullptr){
        IntNode *deleteNode = currVal ;
        currVal = currVal -> next ;
        delete deleteNode ;
    }
}

void IntList::push_front(int data){
    IntNode* addNode = new IntNode(data);

    addNode -> next = head ;
    head = addNode ;
}

void IntList::pop_front(){
    if (head -> next == nullptr){
        IntNode* tempNode = head -> next;
        head = nullptr ;
        delete tempNode ;
    }

    else {
        IntNode* tempNode = head ;
        head = head -> next ;
        delete tempNode ;
    }
}

bool IntList::empty() const {
    if (head == nullptr){
        return true ;
    }

    else {
        return false ;
    }
}

const int & IntList::front() const{
    return head -> value;
}

const int & IntList::back() const{
    IntNode *currVal = head ;

    while (currVal-> next != nullptr){
        currVal = currVal -> next ;
    }

    return currVal -> value;
}

ostream & operator<<(ostream& o, const IntList& oIntList){
    IntNode *currVal = oIntList.head ;

    while (currVal != nullptr) {
        o << currVal -> value ;

        if (currVal -> next != nullptr){
            o << " " ;
        }

        currVal = currVal -> next ;
    }
    return o ;
}

