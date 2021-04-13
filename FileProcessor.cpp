#include "FileProcessor.h"

using namespace std;
FileProcessor::FileProcessor(){

}
FileProcessor::~FileProcessor(){

}

string FileProcessor::loadLineFromFile(string inputFile,int lineNumber){//takes in line at line number and returns it as a string
  ifstream inFile;
  inFile.open (inputFile);
  if (!inFile.is_open()) {
    cout<<"Something went wrong, check the name of the file"<<endl;
  }
  string toRet = "";
  for (int i = 0; i < lineNumber;++i){
    getline(inFile, toRet);
    int pos = 0;
    while ((pos = toRet.find ("\n",pos)) != string::npos) //https://texthandler.com/info/remove-line-breaks-c/
    {
      pos = pos+1;
      toRet.erase ( pos, 2 );
    }

  }
  inFile.close();
  return toRet;
}
