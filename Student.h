#include <iostream>

using namespace std;

class Student{
  public:
    Student();
    Student(int timeNeeded);
    Student(const Student& s);
    ~Student();

    void addTimeWaited();
    void setAtWindow(bool condi);
    void setTimeToSpend(int time);

    int timeToSpend;
    int timeWaited;
    bool atWindow;
};
