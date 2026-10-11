#include <iostream>
using namespace std;

#include "IntList.h"

IntList::IntList() : head(nullptr), tail(nullptr) {}

IntList::~IntList() {
    while (head != nullptr) {
        IntNode* temp = head ;
        head = head->next ;
        delete temp ;
    }
    delete head ;
    head = tail = nullptr ;
}

void IntList::clear() {
    while (head != nullptr) {
        IntNode* temp = head ;
        head = head -> next ;
        delete temp ;
        temp = nullptr ;
    }
    head = tail = nullptr ;
}

void IntList::push_back(int value) {
    IntNode *temp = new IntNode(value) ;

    if(head == nullptr) {
        head = tail = temp ;
        temp->next = nullptr ;
    }
    else {
        temp -> next = nullptr ;
        tail -> next = temp ;
        tail = temp ;
    }
}

void IntList::push_front(int value) {
    IntNode* temp = new IntNode(value) ;

    if (head == nullptr) {
        temp->next = nullptr ;
        head = tail = temp ;
    }
    else {
        temp->next = head ;
        head = temp ;
    }
}

void IntList::pop_front() {
    if (head == nullptr) {
        head = tail = nullptr ;
    }
    else{
        IntNode *temp = head ;
        head = head->next ;
        delete temp ;
        temp = nullptr ;
    }
}

bool IntList::empty() const { 
    return head == nullptr ;
}

const int &IntList::front() const {
    return head->value ;
}

const int &IntList::back() const {
    return tail->value ;
}

ostream &operator<<(ostream &out, const IntList &rhs) {
    for (auto i = rhs.head; i != nullptr; i = i->next) {
        out << i -> value ;
        if (i -> next != nullptr){
            out << " " ;
        }
    }
    return out;
}

void IntList::insert_ordered(int value) {
    IntNode *temp = new IntNode(value) ;
    if (head == nullptr) {
        push_back(value) ;
        delete temp ;
        temp = nullptr ;
    } 
    else if (head -> next == nullptr) {
        if (value > head -> value){
            push_back(value) ;
        }
        else{
            push_front(value) ;
        }
        delete temp ;
        temp = nullptr ;
    }
    else if(temp -> value < head -> value) {
        push_front(value) ;
        delete temp ;
        temp = nullptr ;
    }
    else if(temp -> value > tail -> value) {
        push_back(value) ;
        delete temp ;
        temp = nullptr ;
    }
    else {
        IntNode* currNode = head ;
        while(currNode -> next != nullptr && currNode -> next -> value < temp -> value) {
            currNode = currNode -> next ;
        }
        temp -> next = currNode -> next ;
        currNode -> next = temp;
    }
}

void IntList::remove_duplicates() {
    if (head != nullptr) {
        IntNode *currNode = head ;
        IntNode *temp = nullptr ;
        while (currNode != nullptr && currNode -> next != nullptr) {
            temp = currNode ;
            while(temp -> next != nullptr) {
                if(currNode -> value == temp -> next -> value) {
                    temp -> next = temp -> next -> next;
                }    
                else {
                    temp = temp -> next;
                }
                if(temp -> next == nullptr) {
                    tail = temp;
                }
            }
            currNode = currNode -> next;
        }
    }
}

IntList::IntList(const IntList &cpy) {
    if(cpy.head == nullptr) {
        head = tail = nullptr ;
    }
    else {
        IntNode *temp = cpy.head ;
        head = tail = nullptr ;
        while(temp != nullptr) {
            int newNodeVal = temp -> value ;
            IntNode *newNode = new IntNode(newNodeVal) ; 
            if(head == nullptr) {
                head = tail = newNode ;
                newNode -> next = nullptr ;
                temp = temp -> next ;
            }
            else {
                tail -> next = newNode ;
                tail = newNode ;
                newNode -> next = nullptr ;
                temp = temp -> next ;
            }
        }
    }
}

IntList &IntList::operator=(const IntList &rhs) {
    if (this != &rhs) {
        clear() ;
        IntNode *temp = rhs.head ;
        while (temp != nullptr) {
            push_back(temp -> value) ;
            temp = temp -> next ;
        }
    }
    return *this ;
}

void IntList::selection_sort() {
    if (head != nullptr) {
        for(IntNode* i = head; i != nullptr; i = i -> next) {
            for(IntNode* j = i -> next; j != nullptr; j = j -> next) {
                if(j -> value < i -> value) {
                    int temp = i->value;
                    i->value = j->value;
                    j->value = temp;
                }
            }
        }
    }
}