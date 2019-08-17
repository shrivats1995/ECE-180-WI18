#include"SFInterval.hpp"
#include<iostream>
#include<string>
#include<cstring>
#include<memory>
SFInterval:: SFInterval()
{
  this->years = 0;
  this->months = 0;
  this-> days = 0;
  this->hours = 0;
  this->minutes = 0;
  this->seconds = 0;
}

SFInterval:: SFInterval(int year, int month, int day, int hours, int minutes, int seconds)
{
  this->years = year;
  this->months = month;
  this-> days = day;
  this->hours = hours;
  this->minutes = minutes;
  this->seconds = seconds;
}


void SFInterval:: setIntVal(int year, int month, int day, int hours, int minutes, int seconds)
{
  this->years = year;
  this->months = month;
  this-> days = day;
  this->hours = hours;
  this->minutes = minutes;
  this->seconds = seconds;
}

SFInterval:: operator const char*()
{
  std::string str;
  str += std::to_string(this->years);
  str+= " years, ";
  str += std::to_string(this->months);
  str+= " months, ";
  str += std::to_string(this->days);
  str+= " days, ";
  str += std::to_string(this->hours);
  str+= " hours, ";
  str += std::to_string(this->minutes);
  str+= " minutes and ";
  str += std::to_string(this->seconds);
  str+= " seconds ";
  char* a  = new char[str.length() + 1];
  strcpy(a, str.c_str());
  a[strlen(a)-1] = '\0';
	std::unique_ptr< char*> ptr (new  char*(a));
	return *ptr;

}
