#include <iostream>
#include "Student.h"
using namespace std;

class Window{
  public:
    Window();
    ~Window();

    void addIdle();
    void addIdle(int i);

    void setActive(bool toSetActive);
    int timeIdle;
    bool active;
};
