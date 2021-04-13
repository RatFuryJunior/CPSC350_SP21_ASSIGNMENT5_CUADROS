#include "RegSimulation.h"
#include <bits/stdc++.h> //used for sort

using namespace std;

RegSimulation::RegSimulation(){
  lineNum = 1;
  numberOfWindows = 0;
  tickNumber = 0;
  inputFileName = "";
  fileEmpty = false;
  simulationIsDone = false;
}

RegSimulation::RegSimulation(string fileName){
  lineNum = 1;
  numberOfWindows = 0;
  tickNumber = 0;
  inputFileName = fileName;
  fileEmpty = false;
  simulationIsDone = false;
}

RegSimulation::~RegSimulation(){

}

void RegSimulation::runSimulation(string testFileName){

  //takes in number of windows/line 1
  bool fileWorks = true;
  try{
    numberOfWindows = stoi(f1.loadLineFromFile(testFileName, lineNum));
  }catch(...){
    fileWorks = false;
    cout<<"Something went wrong, check file name and see that it exists"<<endl;
  }

  Window registrarWindows[numberOfWindows];
  Student* registrarStudents[numberOfWindows];

  for(int i = 0; i < numberOfWindows; i++){
    registrarStudents[i] = new Student();
  }

  for (int i = 0; i < numberOfWindows; i++){
    registrarWindows[i] = Window();
  }
  lineNum = lineNum + 1;

  int z = 0;
  simulationIsDone = false;


  if(fileWorks){
    while(true){
      z = z +1;
      if(z > 100000){
        cout<< "Over 100000 round numbers past, stopping simulation"<<endl;
        break;
      }
      int roundTickNumber = -1;


      //checking if tick is tick for more students to enter
      if(!fileEmpty){
        try{
          roundTickNumber = stoi(f1.loadLineFromFile(testFileName, lineNum));
        }catch(...){
          fileEmpty = true;
        }
        if(roundTickNumber == tickNumber){
          lineNum = lineNum + 1;
          roundOfStudents();
        }
      }


      //iterates windows idle time by one if they are inactive
      for (int i = 0; i < numberOfWindows; i++){
        if(!registrarWindows[i].active){
          // cout<<"Window " <<i<<" has a idle time of "<< registrarWindows[i].timeIdle << endl;
          registrarWindows[i].addIdle();
        }
      }

      //sees if student is done
      for(int i = 0; i < numberOfWindows; i++){
        if(registrarWindows[i].active && registrarStudents[i]->timeToSpend == 0){
          // cout<<"Student " <<i <<" is now done"<<endl;
          registrarWindows[i].setActive(false);
          registrarStudents[i]->setAtWindow(false);
          // cout<<"Student "<< i << " Left after waiting " <<registrarStudents[i]->timeWaited<<endl;
          studentsLeft.enqueue(registrarStudents[i]->timeWaited);
        }
      }


      //attaches student from line to window if window is inactive
      for(int i = 0; i < numberOfWindows; i++){
        if(!registrarWindows[i].active && !studentsLine.isEmpty()){
          // cout<<"Student is placed at " <<i<<endl;
          Student *studentToMove = studentsLine.remove();
          registrarWindows[i].setActive(true);
          registrarStudents[i] = studentToMove;//problem line???
          registrarStudents[i]->setAtWindow(true);
          // studentsLine.remove();
        }
      }

      //itterates student time by one
      for(int i = 0; i < numberOfWindows; i++){
        if(registrarStudents[i]->atWindow){
          registrarStudents[i]->timeToSpend = registrarStudents[i]->timeToSpend -1;
          // cout<<"Student" << i << "Needs "<< registrarStudents[i]->timeToSpend <<" and waited " << registrarStudents[i]->timeWaited<<endl;
        }
      }

      //itterates student time waited by one inside the queue
      Student* studentsCopyArray [studentsLine.getSize()];
      int arraySize = studentsLine.getSize();
      int i = 0;
      while(!studentsLine.isEmpty()){
        Student* toAdd = studentsLine.remove();
        toAdd->addTimeWaited();
        studentsCopyArray[i] = toAdd;
        i++;
      }
      for(int i = 0; i < arraySize;i++){
        Student* toAdd = studentsCopyArray[i];
        studentsLine.enqueue(toAdd);
      }


      //iterates tick number for next cycle of while loop
      tickNumber = tickNumber+1;

      //Checks if the simulation is over: does check on queue and windows being empty
      if(studentsLine.isEmpty() && lineNum > 3){
        bool occupiedCheck = false;
        for(int i = 0; i < numberOfWindows;i++){
          if(registrarWindows[i].active){
            occupiedCheck = true;
          }
        }
        if(!occupiedCheck){
          simulationIsDone = true;
        }
      }

      //Runns end of simulation statistics
      if(simulationIsDone){
        cout<<endl<<" ::SIMULATION IS DONE:: "<<endl;
        cout<<studentsLeft.getSize()<<" Students visited the registrar."<<endl<<endl;
        //createEndingStats for Students:
        endOfRoundStatsForStudents();

        // createEndingStats for windows
        int sumOfWindowIdle = 0;
        int maxWindowIdle = 0;
        int numberIdleOverFive = 0;
        for (int i = 0; i < numberOfWindows;i++){
          if(registrarWindows[i].timeIdle > maxWindowIdle){
            maxWindowIdle = registrarWindows[i].timeIdle;
          }
          if(registrarWindows[i].timeIdle>5){
            numberIdleOverFive++;
          }
          sumOfWindowIdle = sumOfWindowIdle + registrarWindows[i].timeIdle;
        }
        // 5. The mean window idle time
        cout<<"Window mean idle time: "<<sumOfWindowIdle/numberOfWindows<<endl;
        // 6. The longest window idle time
        cout<<"Window Longest idle time: "<<maxWindowIdle<<endl;
        // 7. Number of windows idle for over 5 minutes.
        cout<<"# of Windows idle for over 5 mins: " <<numberIdleOverFive<<endl;
        cout<<endl;
        break;
      }
    }
  }else{
    cout<<"Simulation was not ran"<<endl;
  }
}

void RegSimulation::endOfRoundStatsForStudents(){
  int i = 0;
  int maxStudentWait = 0;
  int count = 0;
  int studentsWaitArray [studentsLeft.getSize()];

  while(!studentsLeft.isEmpty()){
    studentsWaitArray[i] = studentsLeft.remove();
    // cout<<i<< " wait array: "<<studentsWaitArray[i] <<endl;

    if(studentsWaitArray[i] > maxStudentWait){
      maxStudentWait = studentsWaitArray[i];
      // cout<<"Max " <<maxStudentWait<<endl;
    }
    if(studentsWaitArray[i] > 10){
      count++;
    }

    i++;
  }

  sort(studentsWaitArray,studentsWaitArray+i);
  // 1. The mean student wait time.
  cout<<"Student mean wait time: "<<getMean(studentsWaitArray, i)<<endl;
  // 2. The median student wait time.
  cout<<"Student median wait time: "<<getMedian(studentsWaitArray, i)<<endl;
  // 3. The longest student wait time.
  cout<<"Student Longest wait time: " <<maxStudentWait<<endl;
  // 4. The number of students waiting over 10 minutes
  cout<<"# of Student wait time over 10 mins: " <<count<<endl;

}

void RegSimulation::roundOfStudents(){
  int numberOfStudentsToAdd = stoi(f1.loadLineFromFile(inputFileName, lineNum));
  lineNum = lineNum + 1;
  for(int i = 0; i <numberOfStudentsToAdd; i++){
    int timeStudentNeeds = stoi(f1.loadLineFromFile(inputFileName, lineNum));
    Student *toEnter= new Student(timeStudentNeeds);
    studentsLine.enqueue(toEnter);
    lineNum = lineNum + 1;
    // cout<<"Added student "<<i<<" needs "<<timeStudentNeeds << " Time"<<endl;

  }

}

float RegSimulation::getMean(int a[], int size){
  float sum = 0;
  for (int i = 0; i<size; i++)
   sum = sum + a[i];
   return sum/size;
}


float RegSimulation::getMedian(int a[], int size){
  float median = 0;
  if (size % 2 == 0){
    median = (a[size/2] + a[size/2 - 1])/2;
  }
  else{
      median = a[size/2];
  }
  return median;
}
