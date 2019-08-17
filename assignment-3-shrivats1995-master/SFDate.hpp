
#ifndef SFDate_hpp
#define SFDate_hpp
#include"SFInterval.hpp"
class SFDateTime;
#include<string>
class SFDate {
public:

	SFDate();                             //default to today

  SFDate(const char *aDateTimeString);  //must parse the given string of the form MM/DD/YYYY

	SFDate(int month, int day, int year); //build date from individual parts

	SFDate(const SFDate &aCopy);

  SFDate(const SFDateTime &aCopy);

	SFDate& operator ++(int); //advance by one day

	SFDate& operator --(int); //back up by one day...

	SFInterval operator-(const SFDate &other) const; //determine interval between two dates...

	SFInterval operator-(const SFDateTime &other) const; //determine interval between two objects...

	SFDate& adjustByDays(int n); // to add or subtract N days from the given date
	SFDate& adjustByWeeks(int n); // to add or subtract N weeks from the given date
	SFDate& adjustByMonths(int n); // to add or subtract N months from the given date
	SFDate& adjustByYears(int n); // to add or subtract N years from the given date

	SFDate& setDay(int aDay);      //set the current day of the given date object; aDay must be in valid range
	SFDate& setMonth(int aMonth);  //set the current month of the given date object aMonth must be in valid range
  SFDate& setYear(int aYear);    //set the current year; must be in valid range

  int   getDay();    //if date is 12/15/2018, the day is the 15th
	int   getMonth();  //if date is 12/15/2018, the month is 12 (dec)
	int   getYear();   //if date is 12/15/2018, the year is 2018

	int   getWeekOfYear(); //if date is 01/10/2018, the week of year is 2 (range is 1..52)
	int   getDayOfYear();  //if date is 01/04/1961, the day of year is 4 (range is 1..365)
	int   getDayOfweek();  //range (0..6 -- 0==sunday)
	int   daysInMonth();   //based on month/year, return # of days in the month

	SFDate& startOfMonth(); //if date is 12/15/2018, return 12/01/2018
	SFDate& endOfMonth();   //if date is 12/15/2018, return 12/31/2018

	SFDate& startOfYear();  //if date is 12/15/2018, return 01/01/2018
	SFDate& endOfYear();    //if date is 12/15/2018, return 12/31/2018

	std::string toDateString();  //Return a string of the form MM/DD/YYYY
	int count_days() const;
// my functions


	bool isLeapYear();
	bool isNextMonth();
	bool isPrevMonth();
	bool isPrevYear();
	bool isNextYear();
	int prevMonth();
	int nextMonth();
	int dec_month();
	int inc_month();
	int inc_year();
	int dec_year();
	int num_days(int prevmonth) ;
	int relat_date(SFDate aVal);
	bool isValidDay(int aDay);
	bool isValidMonth(int aMonth);
	bool isValidYear(int aYear);


	    //ADD RELATIONAL OPERATORS HERE... >, <, <=, >=, !=, ==
	bool operator<(const SFDate &aString);
	bool operator>(const SFDate &aString);
	bool operator<=(const SFDate &aString);
	bool operator>=(const SFDate &aString);
	bool operator==(const SFDate &aString);
	bool operator!=(const SFDate &aString);
	  //... other members here as necessary...
	static int lowM[4];
  static int highM[7];

protected:
	int day, month, year;
};
int incr_month(int month);

#endif /* SFDate_hpp */
