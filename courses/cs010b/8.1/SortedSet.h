#ifndef SORTEDSET_H
#define SORTEDSET_H

#include "IntList.h"

using namespace std;

class SortedSet : public IntList {
    public:
        SortedSet();
        SortedSet(const SortedSet& );
        SortedSet(const IntList& );
        ~SortedSet();

        bool in(int data);
        const SortedSet operator|(const SortedSet&);
        const SortedSet operator&(const SortedSet&);

        void add(int data);
        void push_front(int data);
        void push_back(int data);
        void insert_ordered(int data);
        SortedSet operator|=(const SortedSet&);
        SortedSet operator&=(const SortedSet&);
    private:

};

#endif