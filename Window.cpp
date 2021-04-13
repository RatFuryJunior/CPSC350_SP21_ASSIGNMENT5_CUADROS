#include "Window.h"

using namespace std;

Window::Window(){
  timeIdle = 0;
  active = false;
}

Window::~Window(){

}

void Window::addIdle(){
  timeIdle = timeIdle + 1;
}


void Window::addIdle(int i){
  timeIdle = timeIdle + i;
}

void Window::setActive(bool toSetActive){
  active = toSetActive;
}
