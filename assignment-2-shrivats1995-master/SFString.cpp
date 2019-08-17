//
//  SFString.cpp
//  class_test
//
//  STUDENT: Your job here is to implement the string class functionality in this file...
//
//

#include "SFString.hpp"
#include<iostream>
#include<cstring>
#include<string>
//variables for memory test
int alloc = 0;
int dealloc =0;
//overloading new operator globally to keep track of allocations
void* operator new(size_t size){ 
	void* ptr= malloc(size);
    	alloc ++;
    	return ptr;
}


//overloading delete pointer to keep track of deallocations
void operator delete(void* ptr) noexcept{
    	free(ptr);	
	dealloc++;	
}
// function to print memory related details
void SFString:: print_mem()
{
	int temp = alloc-dealloc;
	
	std::cout<<"Number of Allocations: "<<alloc<<std::endl;
	std::cout<<"Number of Deallocations: "<<dealloc<<std::endl;
	if(temp!=0)
		std::cout<<"Memory Leak....: "<<temp<<std::endl;
	else
		std::cout<<"No memory leak... :)"<<std::endl;
} 

size_t SFString ::getLength() // get string length
{
	return this->length;
}

char* SFString ::getSFString() // get string
{
	return this->buffer;
}

SFString:: SFString () // default constructor
{
	std::cout<<"entering default constructor"<<std::endl;
	length = 0;	
	buffer =new char[length];
	
}

SFString:: ~SFString () // destructor
{
	//std::cout<<"Entering Destructor"<<std::endl;
	if(buffer!=nullptr)
	{
		delete[] buffer;
		buffer = nullptr;
		length =0;
	}
}


SFString:: SFString(const SFString &aString) // copy constructor
{
	
	this->buffer = nullptr;
	if(aString.buffer != nullptr)
	{
		this->buffer = new char[aString.length+1]; // create with new length
		strcpy(this->buffer, aString.buffer);
		this->length = aString.length;
	}
	
}

SFString:: SFString(const char *aString) // conversion constructor
{
	if(aString != nullptr)
	{	//assign length and value to SFString
		this->length = strlen(aString)+1;
		this->buffer = new char[length];
		strcpy(this->buffer, aString); 
		
	}	
}

SFString& SFString:: operator=(const char* aString) // assignment operator for char*
{
	delete[] this->buffer;
	this->length = strlen(aString);
	this->buffer = new char[length];
 	strcpy(this->buffer, aString); // assign value to buffer
	return *this;
	
}

SFString& SFString:: operator=(const SFString& aString) // assignment operator for sfstring
{
	if(this == &aString)
	{
		std::cout<<"Bad Assignment. Same operands on both sides"<<std::endl;
		return *this;	
	}
	
	delete[] this->buffer;	
	if(aString.buffer != nullptr)
	{
		std::cout<<aString.length<<std::endl;
		this->buffer = new char[aString.length];
		strcpy(this->buffer, aString.buffer);
		this->length = aString.length;  // assign length and value
	}
	else
	{
		this->buffer =nullptr;
		this->length = 0;
	}
	return *this;
}


SFString:: operator const char*() const //conversion operator
{
	return buffer;
}

char SFString:: operator[](int pos) const 
{
	if(pos<0 || pos> length-1)
	{
		std::cerr<<"Bad position. out of bounds."<<std::endl;
		return -1;
	}
	else
	{
		if(buffer != nullptr)
		{
			return buffer[pos];	//for valid pos, return value
		}
		else
	
		{
			std::cout<<"Empty String"<<std::endl; //else empty string
			return -1;	
		}
	}
}

SFString& SFString:: operator+=(const char* aString)
{
	
	if(aString !=nullptr)
	{
		length = length + strlen(aString);
		char* temp = new char[length]; // create new variable with a larger size
		strcpy(temp, buffer);
		
		delete[] buffer;
		buffer = nullptr;
		buffer = temp;      
		// delete temp buffer and concatenate to original
		strcat(buffer, aString);
		
		temp = nullptr;	
		delete[] temp;	
			
	}
	return *this;
}


SFString& SFString:: operator+=(const SFString &aString)
{
	std::cout<<"Entering +="<<std::endl;
	if(aString.buffer !=nullptr)
	{
		
		length = length + aString.length;
		char* temp = new char[length]; // create new variable with a larger size
		strcpy(temp, buffer); 
		delete[] buffer;
		buffer = nullptr;
		buffer = temp;
		length = strlen(buffer);
		temp = nullptr;
		delete[] temp;	
		strcat(buffer, aString.buffer);		// add value to original
 			
	}
	return *this;
	
}


// use strcmp for the relational operators

bool SFString:: operator<(const SFString &aString) // less than
{
	if(strcmp(buffer, aString.buffer) <0)
		return true;
	else
		return false;			
}

bool SFString:: operator<(const char *aString)
{
	if(strcmp(buffer, aString) <0)
		return true;
	else
		return false;			
}

bool SFString:: operator>(const SFString &aString) // greater than
{
	if(strcmp(buffer, aString.buffer) >0)
		return true;
	else
		return false;			
}

bool SFString:: operator>(const char *aString)
{
	if(strcmp(buffer, aString) >0)
		return true;
	else
		return false;			
}


bool SFString:: operator>=(const SFString &aString) // greater than equal
{
	if(strcmp(buffer, aString.buffer) >=0)
		return true;
	else
		return false;			
}

bool SFString:: operator>=(const char *aString)
{
	if(strcmp(buffer, aString) >=0)
		return true;
	else
		return false;			
}

bool SFString:: operator<=(const SFString &aString) // less than equal
{
	if(strcmp(buffer, aString.buffer) <=0)
		return true;
	else
		return false;			
}

bool SFString:: operator<=(const char *aString)
{
	if(strcmp(buffer, aString) <=0)
		return true;
	else
		return false;			
}

bool SFString:: operator==(const SFString &aString) // equal 
{
	if(strcmp(buffer, aString.buffer) ==0)
		return true;
	else
		return false;			
}

bool SFString:: operator==(const char *aString)
{
	if(strcmp(buffer, aString) ==0)
		return true;
	else
		return false;			
}

bool SFString:: operator!=(const SFString &aString) // not equal
{
	if(strcmp(buffer, aString.buffer) !=0)
		return true;
	else
		return false;			
}

bool SFString:: operator!=(const char *aString)
{
	if(strcmp(buffer, aString) !=0)
		return true;
	else
		return false;			
}

// array print function
void printarray(char*a,size_t length)
{
	for(int i=0;i< length; i++)
		std::cout<<a[i]<<" ";
	std::cout<<std::endl;
}

SFString&  SFString:: insert(size_t aPos, const char *aString)
{
		size_t len = length + strlen(aString);
		char* temp1 = new char[length - aPos]; // new buffer length
		
		strcpy(temp1, buffer + aPos );		
		char* temp2 = new char[len];
		strncpy(temp2, buffer, aPos);
		temp2[aPos] = '\0';
		delete[] buffer; 
		buffer = nullptr;
		strcat(temp2, aString); // create substrings and attach to substrings
		strcat(temp2, temp1);
		buffer = temp2;
		temp2 = nullptr;
		delete[] temp2;
		delete[] temp1;
		temp1 = nullptr; // delete temp variables
		length = strlen(buffer);
	
	return *this;
}

SFString&  SFString:: insert(size_t aPos, const SFString &aString) // insert sfstring
{
	return(this->insert(aPos, aString.buffer)) ;
		
}




SFString&  SFString:: insert(size_t aPos, const char aChar) // insert one character
{
	
	
	
		char* temp = new char[length+1];
		strcpy(temp, buffer);
		delete[] buffer;
		int i =0;
		buffer = nullptr;
		for(i=length-1;i>=aPos;i--)
			temp[i+1] = temp[i]; // shift elements by one position to insert new char
		
		temp[i+1] = aChar;
		buffer = temp;
		length = strlen(buffer);
		temp = nullptr;
		delete[] temp;
	
	return *this;
}


SFString&  SFString::  erase(size_t aPos, size_t aLength)
{ 

	if(aPos>length-1)
		std::cout<<"Bad position. Out of Bounds. Erase error"<<std::endl;
	else if (aLength > (length - aPos))
	{	// when length exceeds remaining lengths
		char* temp1 = new char[aPos+1];
		strncpy(temp1, buffer , aPos); //delete everything after aPos
		temp1[aPos] = '\0';	
		delete[] buffer; 
		buffer = nullptr;
		buffer = temp1; 
		temp1 = nullptr;
		delete[] temp1;
		length = strlen(buffer);
	}
	else
	{ //create substring delete and reattach
		char* temp1 = new char[length - aLength+1];
		strncpy(temp1, buffer, aPos);
		temp1[aPos] = '\0';
		strcat(temp1, buffer + aPos + aLength);
		delete[] buffer;
		buffer = nullptr;
		buffer = temp1;
		temp1 = nullptr;
		delete[] temp1;
		length = strlen(buffer);
	
	
			
	}
	return *this;
	 
}
	

SFString&   SFString:: replace(size_t pos, size_t len, const char *aString)
{
	std::cout<<"entering replace SFString"<<std::endl;
	if(pos>length-1)
		std::cout<<"Bad position. Out of Bounds"<<std::endl;
	else
	{	// replace is erase followed by insert
		this->erase(pos, len);
		this->insert(pos, aString);
		length = strlen(buffer);	
	
	}
	return *this;

		
}	

SFString&   SFString:: replace(size_t pos, size_t len, const SFString &aString) // replace function
{
	std::cout<<"entering replace SFString"<<std::endl;
	if(pos>length-1)
		std::cout<<"Bad position. Out of Bounds"<<std::endl;
	else
	{	// replace is erase followed by insert
		this->erase(pos, len);
		this->insert(pos, aString);
		length = strlen(buffer);
	}
	
	return* this;
		
}



int   SFString:: find(const char *aString, size_t offset)
{	
	int ret;
	char* temp1 = strstr(buffer + offset, aString); // use strstr to find first pccurence from offset
	if(temp1==nullptr)
	{
		return -1;
	}
	else
	{
		ret = (((int)(temp1 - buffer)) )/sizeof(char) ; // subtract memory indices to get position
		temp1 = nullptr; // temp
		delete[] temp1;
		return ret;
	}	
}


int   SFString:: find(const SFString &aString, size_t offset)
{	
	return(this->find(aString.buffer, offset));
}


//extra credit operators

 SFString operator+(const SFString& lhs, const SFString& rhs) // friend function for sfstring  + sfstring
{	SFString res; // create object
	std::cout<<"Entering +sf,sf"<<std::endl;
	if(rhs.buffer !=nullptr && lhs.buffer != nullptr)
	{
		SFString res(lhs);
		res+=rhs;
	}
	return res; // return object
		
}

 SFString operator+(const SFString& lhs, const char* rhs) // friend function for sfstring  + char*
{

	SFString res(lhs);
	res+=rhs;

	
	return res; // return object
}
 
 SFString  operator+(const char* lhs, const SFString& rhs) // friend function for char *  + sfstring
{
	
	SFString res(lhs);
	res+=rhs;
	
	return res; // return object
} 


