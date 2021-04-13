#include <iostream>
#include "FileProcessor.h"
#include "Window.h"
#include "genqueue.h"

using namespace std;

class RegSimulation{
  public:
    RegSimulation();
    RegSimulation(string fileName);
    ~RegSimulation();
    void runSimulation(string testFileName);
    FileProcessor f1 = FileProcessor();
    GenQueue <Student*> studentsLine;
    GenQueue <int> studentsLeft;

  protected:
    void roundOfStudents(); //used to add students
    void endOfRoundStatsForStudents(); //prints end of round stats
    float getMean(int a[], int size);
    float getMedian(int a[], int size);
    int tickNumber;
    int lineNum;
    int numberOfWindows;
    string inputFileName;
    bool fileEmpty;
    bool simulationIsDone;
  };
