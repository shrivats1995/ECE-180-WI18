//
//  SFStringTester.cpp
//  class_test
//

#include "SFStringTester.hpp"
#include "SFString.hpp"
#include <cstring>
#include <iostream>
#include <chrono>

//#include <ctime>

//compare results and return error status (side-effect output to terminal)...
int compare(const SFString& str1, const std::string &str2, const char* aMessage) {
  const char* s1=str1;
  const char* s2=str2.c_str();
  
  std::cout << "Test: " << aMessage;
  if(strcmp(s1,s2)) {
    std::cout << " Error! s1(" << s1 << ") s2(" << s2 << ")" << std::endl;
    return 1;
  }
  
  std::cout << " ok " << std::endl;
  return 0;
}

//compare int results and return error status (side-effect output to terminal)...
int compare(int anArg1, int anArg2,const char* aMessage) {
  std::cout << "Test: " << aMessage;
  if(anArg1!=anArg2) {
    std::cout << " Error! " << std::endl;
    return 1;
  }
  std::cout << " ok " << std::endl;
  return 0;
}

//run your own performance stress-tests here...
void runPerformanceTests() {
  
  //STUDENTS: ADD YOUR CODE HERE...

	char* huge_val = new char[200];
	strcpy(huge_val, " This is a very big string that i am going to use to test the performnce of my string class. I hope that this hugee string can serve that purpose. this is a very large string"); // huge string!!
	std::cout<<"\n\n";
	std::cout<<"PERFORMANCE TESTS!!!!!\n\n";


	auto start = std::chrono::system_clock::now(); // start timer
	std::string s1 = huge_val; //std:: string construction
	auto end = std::chrono::system_clock::now();
	std::cout<< "std::String Conversion Constructor took "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count() << " nanoseconds to run.\n";
	
	
   	auto start1 = std::chrono::system_clock::now();
	SFString sf1 = huge_val; //sf string construction
	auto end1 = std::chrono::system_clock::now();
	std::cout<<"SFString Conversion Constructor took "<<std::chrono::duration_cast<std::chrono::nanoseconds>(end1-start1).count() << " nanoseconds to run.\n\n";

	// measure += operation in a lopp running ten times

	// for std::string
	auto start2 = std::chrono::system_clock::now();
	for(int i=0;i<10;i++)
		s1 += huge_val;
	auto end2 = std::chrono::system_clock::now();
	std::cout<< "std::String += operator running 100 times took "<<std::chrono::duration_cast<std::chrono::microseconds>(end2-start2).count() << " microseconds to run.\n";
	
	// for sfString
	auto start3 = std::chrono::system_clock::now();
	for(int i=0;i<10;i++)
		sf1 += huge_val;
	auto end3 = std::chrono::system_clock::now();
	std::cout<< "SFString += operator running 100 times took "<<std::chrono::duration_cast<std::chrono::microseconds>(end3-start3).count() << " microseconds to run.\n\n";

	delete[] huge_val;
	huge_val = nullptr;
	std::cout<<"\n\n";
}

//run your own performance stress-tests here...


void runMemoryTests() {
  
  //STUDENTS: ADD YOUR CODE HERE...
	std::cout<<"MEMORY TESTS!!!!!\n\n";
	SFString::print_mem();
	std::cout<<"\n\n";
}

//compare construction operations against std::string...
int runConstructionTests() {
  int theResult=0;
  SFString sf1;
  std::string s1;
  theResult+=compare(sf1,s1,"ctor()");
  
  const char* theStr="teststring";
  SFString sf2(theStr);
  std::string s2(theStr);
  theResult+=compare(sf2,s2,"ctor(const char*)");
  
  SFString sf3(sf2);
  std::string s3(s2);
  theResult+=compare(sf3,s3,"ctor(const SFString&)");
  
  return theResult;
}



//compare assignment operations against std::string...
int runAssignmentTests() {
  int theResult=0;
  
  const char* theStr="assignment string";
  SFString sf1(theStr);
  SFString sf2; sf2=sf1;
  
  std::string s1(theStr);
  std::string s2; s2=s1;
  theResult+=compare(sf2,s2,"operator=(const SFString&)");
  
  SFString sf3; sf3=theStr;
  
  std::string s3; s3=theStr;
  theResult+=compare(sf2,s2,"operator=(const char*)");
  
  return theResult;
}

//compare concatenation operations against std::string...
int runConcatenationTests() {
  int theResult=0;
  
  const char* theStr1="concat1";
  const char* theStr2=" concat2";
  
  SFString sf1(theStr1);
  SFString sf2(theStr2);
  SFString sf_temp = sf1+=sf2;
  
  std::string s1(theStr1);
  std::string s2(theStr2);
  std::string s_temp = s1+=s2;
  
  theResult+=compare(sf_temp,s_temp,"operator+=(const SFString&)");
  
  sf_temp = sf1+=theStr2;
  s_temp = s1+=theStr2;
  
  theResult+=compare(sf_temp,s_temp,"operator+=(const const char*)");
  
  return theResult;
}

//compare relational operations against std::string...
int runRelationalTests() {
  int theResult=0;
  
  const char* theStr1="concat1";
  const char* theStr2=" concat2";
  
  SFString sf1(theStr1);
  SFString sf2(theStr2);
  std::string s1(theStr1);
  std::string s2(theStr2);
  
  theResult+=compare(sf1==sf2, s1==s2, "operator==()");
  theResult+=compare(sf1!=sf2, s1!=s2, "operator!=()");
  theResult+=compare(sf1<sf2, s1<s2, "operator<()");
  theResult+=compare(sf1<=sf2, s1<=s2, "operator<=()");
  theResult+=compare(sf1>sf2, s1>s2, "operator>()");
  theResult+=compare(sf1>=sf2, s1>=s2, "operator>=()");
  
  return theResult;
}

//compare insertion operations against std::string...
int runInsertionTests() {
  int theResult=0;
  
  const char* theStr1="insert1";
  const char* theStr2="substr";
  
  SFString sf1(theStr1);
  SFString sf2(theStr2);
  sf1.insert(3,sf2);
  
  std::string s1(theStr1);
  std::string s2(theStr2);
  s1.insert(3,s2);
  
  theResult+=compare(sf1,s1,"insert(int, const string&)");
  
  sf2.insert(3, "something");
  s2.insert(3, "something");
  theResult+=compare(sf2,s2,"insert(int, const char*)");
  
  return theResult;
}

void runInsertTests() {
  
  const char* theStr1="insert1";

  
  SFString sf1(theStr1);
  sf1.insert(3,'a');
  std::cout<<"insert char: "<<sf1.getSFString()<<std::endl;
  
}

//compare erase operations against std::string...
int runEraseTests() {
  int theResult=0;
  
  const char* theStr1="this is a long string that is testing erase";
  
  SFString sf1(theStr1);
  sf1.erase(15,50);
  std::string s1(theStr1);
  s1.erase(15,50);
  std::cout<<"sf1: "<<sf1<<std::endl;
  std::cout<<"s1: "<<s1<<std::endl;
  theResult+=compare(sf1,s1,"erase(int, const string&)");
  
  return theResult;
}

//compare replacement operations against std::string...
int runReplacementTests() {
  int theResult=0;
  
  const char* theStr1="original string";
  const char* theStr2="replacement";
  
  SFString sf1(theStr1);
  SFString sf2(theStr2);
  sf1.replace(9, 6, sf2);
  std::cout<<"sf1: "<<sf1<<std::endl;
  std::string s1(theStr1);
  std::string s2(theStr2);
  s1.replace(9, 6, s2);
    std::cout<<"s1: "<<s1<<std::endl;
  theResult+=compare(sf1,s1,"replace(int, int, const string&)");
  
  sf2.replace(3, 3, "new");
  s2.replace(3, 3, "new");
  
  theResult+=compare(sf2,s2,"replace(int, int, const char*)");
  
  return theResult;
}

//compare searching operations against std::string...
int runFindTests() {
  int theResult=0;
  
  const char* theStr1="original string contains string twice";
  const char* theStr2="string";
  
  SFString sf1(theStr1);
  SFString sf2(theStr2);
  
  std::string s1(theStr1);
  std::string s2(theStr2);
  
  theResult+=compare((int)sf1.find(sf2,5), (int)s1.find(s2,5),"find(const string&, size_t)");
  theResult+=compare((int)sf1.find("ring",20), (int)s1.find("ring",20),"find(const char*, size_t)");

  return theResult;
}

//only called if the STUDENT explicitly asks us to do it in main...
int runExtraCreditTests() {
  int theResult=0;
  
  const char* thePrefix="hello";
  const char* theSuffix=" there ";
 
 
 
  SFString sf1(theSuffix);
  SFString sf2 = thePrefix + sf1;
  
  std::string s1(theSuffix);
  std::string s2 = thePrefix + s1;
  
  theResult+=compare(sf2,s2,"operator+(const char*, const SFString&)");


  SFString sf3(thePrefix);
  SFString sf4 = sf3 + theSuffix ;
  
  std::string s3(thePrefix);
  std::string s4 = s3 + theSuffix;
  
  theResult+=compare(sf4,s4,"operator+(const SFString&, const char*)");
  

 
  return theResult;
}


int SFStringTester::runTests() {
  
  int theErrors=0;
  theErrors+=runConstructionTests();
  theErrors+=runAssignmentTests();
  theErrors+=runConcatenationTests();
  theErrors+=runRelationalTests();
  theErrors+=runInsertionTests();
  theErrors+=runEraseTests();
  theErrors+=runReplacementTests();
  theErrors+=runFindTests();

  theErrors+=runExtraCreditTests();
  runInsertTests();  
  runPerformanceTests();
  runMemoryTests();
	
  std::cout << theErrors << " errors found -- " << (theErrors ? "too bad!" : "woot!") << std::endl;
  return theErrors;
}
