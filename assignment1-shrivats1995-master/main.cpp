//
//  main.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#include "ProcessController.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
  
    //STUDENTS: Set this variable to the project path of the root of your local assignment folder...
  const char *theProjectPath ="/home/shrivats/new180code1/assignment1-shrivats1995-master/";

  ProcessController theController(theProjectPath);
  theController.runTests().runActual();
  
  return 0;
}
