#include "Student.h"

using namespace std;

Student::Student(){
  timeToSpend = 0;
  timeWaited = 0;
  atWindow = false;
}

Student::Student(const Student& s){
  timeToSpend = s.timeToSpend;
  timeWaited = s.timeWaited;
}

Student::~Student(){

}
Student::Student(int timeNeeded){
  timeToSpend = timeNeeded;
  timeWaited = 0;
}

void Student::addTimeWaited(){
  timeWaited = timeWaited + 1;
}

void Student::setTimeToSpend(int time){
  timeToSpend = time;
}

void Student::setAtWindow(bool condi){
  atWindow = condi;
}
