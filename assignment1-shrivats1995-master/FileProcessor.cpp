//
//  FileProcessor.cpp
//  ece180-assignment1
//
//  Created by rick gessner on 1/10/18.
//

#include "FileProcessor.hpp"

#include <iostream>
#include <fstream>
#include <math.h>
#include<string>
#include<sstream>
#include<ctype.h>
#include<algorithm>
#include<vector>
#include<map>


FileProcessor::FileProcessor(const std::string aPath) : rootPath(aPath) {
  //complete the initialize process, if any...
}

/*
 * STUDENT: ProcessController calls this for each of your word-files
 */
FileProcessor& FileProcessor::run(const char* aFilename) {
  std::string theFullPath = rootPath + std::string("/content/") + std::string(aFilename);
  
  //--------------------------------------------------------
  // STUDENTS: Add code here to perform assignment tasks...
  //--------------------------------------------------------
  

	std::vector<std::string> stopwords;
	std::vector<std::string> wlist;
	std::string stopdata;
	std::fstream obj;
	// store stop words
	obj.open(rootPath + "/content" + "/stopwords.txt");
	while (getline(obj, stopdata, ','))
	{
		stopwords.push_back(stopdata);
	}
	obj.close();
	for (int i = 1; i < stopwords.size(); i++)
	{
		stopwords[i] = stopwords[i].erase(0, 1);
	}
	
	
	/*for (int i=0;i<stopwords.size();i++)
	{
		std::cout<<stopwords[i]<<std::endl;	
	}*/


	
	int count = 0;
	int flag = 0; // flag is raised on meeting stopword/digit 
	std::string data;
	obj.open(theFullPath);
	std::map <std::string, int> word_count;
	std::map <std::string, int>::iterator wciter; // initialize iterators
	std::map <std::string, int>::iterator wcitern;	
	
	// get data 
	while (getline(obj, data))

	{
		std::istringstream iss(data);
		std::string token;

		// read word by word
		while (iss >> token)
		{

			int i = 0;
			for (i; i < token.length(); i++)
			{

				flag = 0;
				if (isdigit(token[i])) {// remove word if it has digits
					flag = 1;
					break;
				}
				else
				{
					if (!isalpha(token[i])) // remove punctuations
					{
						token.erase(i, 1);
						i--;
					}
				}
			}
			

			if (flag == 0) { // if flag is not set, store in map for part 1 and in a vector for use in part 2

				std::transform(token.begin(), token.end(), token.begin(), ::tolower);
				for (i = 0; i < token.length(); i++)
				{
					if (token[i] < 97 || token[i]>122)
					{
						token.erase(i, 1);
						i--;
					}
				}
				if (token.length() != 0)
				{
					wlist.push_back(token); // store in wlist vector
					this->file_count++;
					//store in map for part 1
					if (this->word_counter.find(token) == this->word_counter.end())
						this->word_counter[token] = 1;
					else
						this->word_counter[token] += 1;
				}

			}

		}
		
	}

	



	obj.close();
	std::vector<std::string> stopw;
	int sto = 0;
	std::pair <std::string, std::string> my_pair;
	//store in a map with two keys for part 2
	std::map<std::pair<std::string, std::string>, int>::iterator biter;
	
	
	// store data in pair of maps for bigrams before removing stopwords
	for(int i = 0;i<wlist.size()-1;i++)
	{
	
		if ((this->bi_map.find(std::make_pair(wlist[i], wlist[i + 1])) == this->bi_map.end()))
		{
			this->bi_map[std::make_pair(wlist[i], wlist[i + 1])] = 1;
		}
		else
		{
			this->bi_map[std::make_pair(wlist[i], wlist[i + 1])] += 1;
		}
	}
	//std::cout << "bimapsize" << bi_map.size() << std::endl;

	// print two key map
	
	double den_sum = 0;
	for (biter = this->bi_map.begin(); biter != this->bi_map.end(); ++biter)
	{
		den_sum = den_sum + biter->second; // calculate occurences of all events
	}
	
	for (biter = this->bi_map.begin(); biter != this->bi_map.end(); ++biter)
	{
		this->probability.push_back(  (double)biter->second / den_sum); // calculate probability
		
	}

	/*for(int i=0;i<this->probability.size();i++)
	{
		std::cout<<std::endl<<this->probability[i]<<std::endl;
	}*/

	//std::cout<<bi_map.size();
	/*for (biter = this->bi_map.begin(); biter != this->bi_map.end(); ++biter)
	
	{
		std::cout<<biter->first.first<<","<<biter->first.second<<":" << biter->second<<std::endl;		
	}*/

//remove stopwrds
	
	//std::cout<<this->wlist.size()<<std::endl;
	for (wciter = this->word_counter.begin(); wciter != this->word_counter.end(); ++wciter)
	{
		std::string tok = wciter->first;

		for (int i = 0; i < stopwords.size(); i++)
		{
			
			if (stopwords[i].compare(tok) == 0)
			{
					
				stopw.push_back(tok);
			}


		}

	}

	for (int i = 0; i < stopw.size(); i++)
	{
		this->word_counter.erase(stopw[i]);
	}

  return *this;
}

