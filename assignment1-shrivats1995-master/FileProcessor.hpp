//
//  FileProcessor.hpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#ifndef FileProcessor_hpp
#define FileProcessor_hpp
#include<iostream>
#include <string>
#include<map>
#include<vector>

class FileProcessor {
public:

  FileProcessor(const std::string aPath);
  
  FileProcessor& run(const char* anInputFilename);

  std::map <std::string, int> word_counter;

  std::map <std::pair<std::string, std::string>, int> bi_map;

  std::vector<double> probability;

  //std::vector<std::string> wlist;
  int file_count;
  
protected:
  std::string rootPath;
};

#endif /* FileProcessor_hpp */
