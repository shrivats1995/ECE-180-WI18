//
//  ProcessController.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/15/18.
//

#include "ProcessController.hpp"
#include <fstream>
#include <iostream>
#include<math.h>
#include <algorithm>


// dot product function
double dot_product(FileProcessor f1,  FileProcessor f2)
{
	double sum = 0.0;
	double den = 0.0;
	double dot = 0.0;
	std::map <std::string, int>::iterator wciter;
	for (wciter = f1.word_counter.begin(); wciter != f1.word_counter.end(); ++wciter)  // run through map to get numerator of dot product
	{
		
		
			if (f2.word_counter.find(wciter->first) == f2.word_counter.end())
				sum = sum + 0;
			else
				sum = sum + (wciter->second * f2.word_counter[wciter->first]);// calculate numerator
		


	}
	std::cout << "entering dot product" << std::endl;
	std::cout << "num" << sum << std::endl;
	double den1 = 0;
	double den2=0;

	// calculate denominator

	for (wciter = f1.word_counter.begin(); wciter != f1.word_counter.end(); ++wciter)
		den1 = den1 + (wciter->second)*(wciter->second);
	for (wciter = f2.word_counter.begin(); wciter != f2.word_counter.end(); ++wciter)
		den2 = den2 + (wciter->second)*(wciter->second);
	den1 = sqrt(den1);
	den2 = sqrt(den2);
	den = den1 * den2;
	std::cout << "den" << den << std::endl;
	
	//den = (f1.file_count) * (f2.file_count);
	dot = sum / den;
	double angle = acos(dot); // return angle
	
	return angle;
	


}

ProcessController::ProcessController(const char *aRootPath) : rootPath(aRootPath) {
}

/*
 * STUDENT: This is where you add code to test your code/classes, as needed...
 */
ProcessController& ProcessController::runTests() {
// run twain lewis and alice. store bigrams for lewis, calculate distance
  std::ofstream testout(rootPath+std::string("/testoutput.txt"));
  std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
  std::cout.rdbuf(testout.rdbuf()); //redirect

  std::cout << "running tests..."  << std::endl;

  // ----------------------------------
  // STUDENTS... Add your tests here...
  // ----------------------------------

  FileProcessor f1(rootPath), f2(rootPath), f3(rootPath);

  f1.run("lewis.txt");
  f2.run("twain.txt");
  f3.run("alice.txt");
  double a12 = dot_product(f1, f2);
  double a13 = dot_product(f1, f3);
  	std::cout << "Distance Lewis-Twain: " << a12 << std::endl;
  	std::cout << "Distance Lewis-Alice: " << a13 << std::endl;
  	std::cout << "Document Lewis is most similar to document " <<((a12< a13)? "Twain":"Alice") << std::endl;

  

  std::ofstream js1(rootPath + "/bigrams_lewis.json");

  std::map<std::pair<std::string, std::string>, int>::iterator biter;


  js1 << "{" << std::endl;
  int i = 0;
  for (biter = f1.bi_map.begin(); biter != f1.bi_map.end(); ++biter)
  {
	  js1 << "\t" << "{" << "\"bigram\"" << " : \"" << biter->first.first << "-" << biter->first.second << "\", " << "\"probability\"" << " : " << f1.probability[i] << "}," << std::endl;
	  i++;
  }
  js1 << "}" << std::endl;

  std::cout.rdbuf(coutbuf); //reset to standard output again
  coutbuf=nullptr;

  return *this;
}

/*
 * STUDENT: This is where you add code to manage the tasks in this assignment...
 */
ProcessController& ProcessController::runActual() {
  return processWordFiles();
}

ProcessController& ProcessController::processWordFiles() {
  FileProcessor f1(rootPath), f2(rootPath), f3(rootPath);

  // --------------------------------------------------------------------
  // STUDENTS... This control logic already works; see FileProcessor.cpp
  // --------------------------------------------------------------------

  f1.run("alice.txt");
  f2.run("verne.txt");
  f3.run("jfk.txt");


  std::ofstream newFile(rootPath + "output1.txt");
  std::ofstream newFile1(rootPath + "output2.txt");
  std::ofstream newFile2(rootPath + "output3.txt");

  
  // write output files

  std::map <std::string, int>::iterator wciter;
  for (wciter = f1.word_counter.begin(); wciter != f1.word_counter.end(); ++wciter)
  {
	
	  newFile << wciter->first << ",";

  }


  for (wciter = f2.word_counter.begin(); wciter != f2.word_counter.end(); ++wciter)
  {
	  
	  newFile1 << wciter->first << ",";

  }
  for (wciter = f3.word_counter.begin(); wciter != f3.word_counter.end(); ++wciter)
  {

	  newFile2 << wciter->first << ",";

  }

  newFile.close();
  newFile1.close();
  newFile2.close();



  std::ofstream js1(rootPath + "/bigrams_alice.json");
  std::ofstream js2(rootPath + "/bigrams_verne.json");
  std::ofstream js3(rootPath + "/bigrams_jfk.json");
  std::map<std::pair<std::string, std::string>, int>::iterator biter;

// write to json files
  js1 << "{" << std::endl;
  int i = 0;
  for (biter = f1.bi_map.begin(); biter != f1.bi_map.end(); ++biter)
  {
	  js1<< "\t" << "{" << "\"bigram\"" << " : \"" << biter->first.first << "-" << biter->first.second << "\", " << "\"probability\"" << " : " << f1.probability[i] << "}," << std::endl;
	  i++;
  }
  js1 << "}" << std::endl;


  js2<< "{" << std::endl;
   i = 0;
  for (biter = f2.bi_map.begin(); biter != f2.bi_map.end(); ++biter)
  {
	  js2 << "\t" << "{" << "\"bigram\"" << " : \"" << biter->first.first << "-" << biter->first.second << "\", " << "\"probability\"" << " : " << f2.probability[i] << "}," << std::endl;
	  i++;
  }
  js2 << "}" << std::endl;

  js3 << "{" << std::endl;
   i = 0;
  for (biter = f3.bi_map.begin(); biter != f3.bi_map.end(); ++biter)
  {
	  js3 << "\t" << "{" << "\"bigram\"" << " : \"" << biter->first.first << "-" << biter->first.second << "\", " << "\"probability\"" << " : " << f3.probability[i] << "}," << std::endl;
	  i++;
  }
  js3 << "}" << std::endl;


  js1.close();
  js2.close();
  js3.close();


  return saveSummary(f1, f2, f3);
}

ProcessController& ProcessController::saveSummary(const FileProcessor &f1, const FileProcessor &f2, const FileProcessor &f3) {

  //theResultFile is filename where you store your summary in assignment root folder...
  const char* theResultFile = "results.txt";

  // ----------------------------------------------------------
  // STUDENTS... Add code here to generate and save summary...
  // ----------------------------------------------------------


	double a12 = dot_product(f1, f2);
  	double a13 = dot_product(f1, f3);

//write result file

	std::cout<<std::endl<<rootPath+ theResultFile<<std::endl;
	std::ofstream result(rootPath + theResultFile);
  	result << "Distance AB: " << a12 << std::endl;
  	result << "Distance AC: " << a13 << std::endl;
  	result << "Document A is most similar to document " <<((a12< a13)? "B":"C") << std::endl;
	result.close();
  return *this;
}
