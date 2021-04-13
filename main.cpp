#include "RegSimulation.h"
#include <iostream>

int main(int argc, char ** argv) {
  string inputChoice = "";
  if(argc > 1){
    inputChoice = argv[1];

    RegSimulation r1 = RegSimulation(inputChoice);
    r1.runSimulation(inputChoice);
  }else{
    cout<<"Enter one string/something for the file name..."<<endl;
  }
  
  cout<<"exited"<<endl;
}
