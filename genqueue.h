#ifndef genqueue_h
#define genqueue_h

#include <iostream>
#include <exception>

#include "ListNode.h"
using namespace std;

template <typename D>
class GenQueue{
  public:
    GenQueue();//default
    ~GenQueue();

    //core functions
    void enqueue(D data);
    D remove(); //aka dequeue


    //aux functions
    D peek();
    bool isEmpty();
    size_t getSize();

  private:
    size_t numElements; // unsigned int
    List<D> *queList;
};

template <typename D>
GenQueue<D>::GenQueue(){
  queList = new DoublyLinkedList<D>();
  numElements = 0;
}

template <typename D>
GenQueue<D>::~GenQueue(){
  delete queList;
}



template <typename D>
void GenQueue<D>::enqueue(D data){
  queList->insertBack(data);
  numElements = numElements +1;
}

template <typename D>
D GenQueue<D>::remove(){
  D toRet = queList->removeFront();
  numElements = numElements -1;
  return toRet;
}

template <typename D>
D GenQueue<D>::peek(){
  D toRet;
  toRet = queList->removeFront();
  queList->insertFront(toRet);
  return toRet;
}

template <typename D>
bool GenQueue<D>::isEmpty(){
  return queList->isEmpty();
}

template <typename D>
size_t GenQueue<D>::getSize(){
  return numElements;
}
#endif
