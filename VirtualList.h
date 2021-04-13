#ifndef VIRTUALLIST_H
#define VIRTUALLIST_H

#include "ListNode.h"
using namespace std;

template <typename D>
class List{
  public:

    virtual void insertFront(D insert) = 0;
    virtual void insertBack(D insert) = 0;
    virtual D removeFront() = 0;
    virtual D removeBack() = 0;

    virtual bool isEmpty() = 0;
    virtual size_t getSize() = 0;

    virtual D peekFront() = 0;
    virtual D peekRear() = 0;

};

#endif
