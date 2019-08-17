//
//  SFString.hpp
//  class_test
//
//  STUDENTS: This interface is incomplete; refer to the assignment readme for detailed instructions!
//

#ifndef SFString_hpp
#define SFString_hpp

#include <string>
//#include<iostream>


class SFString {
public:
  
	SFString();
  	SFString(const SFString& aString); // copy constructor
  
  	SFString(const char *aString); //converting constructor
  
  	SFString&    operator=(const SFString& aString); // assignment operator
  
  	SFString&    operator=(const char *aString); 

	~SFString();
  
  	/*yet to be tested*/operator const char*() const;
  
  	char         operator[](int pos) const;  

  	SFString&    operator+=(const SFString &aString);
  
  	SFString&    operator+=(const char *aString); 
  
  	bool         operator<(const SFString &aString);
  	bool         operator<(const char *aString);
  
  	bool         operator<=(const SFString &aString);
  	bool         operator<=(const char *aString);
  
  	bool         operator>(const SFString &aString);
  	bool         operator>(const char *aString);
  
  	bool         operator>=(const SFString &aString);
  	bool         operator>=(const char *aString);
  
  	bool         operator==(const SFString &aString);
  	bool         operator==(const char *aString);
  
  	bool         operator!=(const SFString &aString);
  	bool         operator!=(const char *aString);
  
  
  	SFString&    insert(size_t aPos, const SFString &aString);
  	SFString&    insert(size_t aPos, const char *aString);  
  
  	SFString&    insert(size_t aPos, const char aChar);
  
  	SFString&    erase(size_t aPos, size_t aLength);

  	SFString&    replace(size_t pos, size_t len, const SFString &aString);
  	SFString&    replace(size_t pos, size_t len, const char *aString);
	
	friend SFString operator+(const SFString& lhs, const SFString& rhs);
	friend SFString operator+(const SFString& lhs, const char* rhs);
 	friend SFString operator+(const char* lhs, const SFString& rhs);
  
  	int          find(const SFString &aString, size_t offset=0);
  	int          find(const char *aString, size_t offset=0);
	size_t	     getLength();
	char*	     getSFString();
	
	static void print_mem();
	

  
private:

	char* buffer; // buffer to store the string
	size_t length; // length of the string	  
  
};


#endif /* SFString_hpp */

 
