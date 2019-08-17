
#ifndef SFTime_hpp
#define SFTime_hpp
#include<string>
#include"SFInterval.hpp"
class SFDateTime;
class SFTime {
public:
  SFTime();                             //default to now(HH:MM:SS)
  SFTime(const char *aTimeString);      //must parse the given string of the form "HH:MM:SS"
  SFTime(int anHour, int aMinutes, int aSeconds); //build time from individual parts
  SFTime(const SFTime &aCopy);
  SFTime(const SFDateTime &aCopy);

  SFTime& adjustByMinutes(int n);// -- to +/- N minutes from the given time
  SFTime& adjustByHours(int n); //-- to +/- N hours from the given time. 11:15pm + 2hours is 1:15a (rolls over)

  SFInterval operator-(const SFTime &other) const; //determine interval between two times...
  SFInterval operator-(const SFDateTime &other) const; //determine interval between two datetime objects...

  int   getHour() ;
  int   getMinutes() ;
  int   getSeconds() ;


  SFTime& startOfDay(); //change time to (00:00:00)
  SFTime& endOfDay();   //change time to (23:59:59)

  std::string toTimeString();  //Returns string of the form HH:MM:SS

  int inc_minutes(int val, bool flag);
  int dec_minutes(int val, bool flag);
  bool checkPosRollover(int h, int m, int s);
  bool checkNegRollover(int h, int m, int s);
  int relat_time(SFTime aCopy);
    //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==
  bool operator<(const SFTime &aString);
  bool operator>(const SFTime &aString);
  bool operator<=(const SFTime &aString);
  bool operator>=(const SFTime &aString);
  bool operator==(const SFTime &aString);
  bool operator!=(const SFTime &aString);
  //... more members here as necessary...
//protected:
  int hours;
  int minutes;
  int seconds;

};

#endif /* SFTime_hpp */
