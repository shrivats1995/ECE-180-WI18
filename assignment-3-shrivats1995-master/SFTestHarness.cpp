//
//  SFTestHarness.cpp
//  ECE180-Assignment3
//
//  Created by rick gessner on 2/12/18.
//

#include "SFTestHarness.hpp"
#include "SFDate.hpp"
#include"SFTime.hpp"
#include"SFDateTime.hpp"
#include"SFTimezone.hpp"
#include"SFInterval.hpp"
#include<iostream>
#include<cstring>
#include<map>
#include<string>
using SoftwareFoundations::SFTestHarness;

int SFTestHarness::runDateTests() {
  int errors = 0;
  SFDate sf1(02, 28, 2018);
  SFDate sf2(03, 01, 2018);
  sf1.adjustByDays(30);
  sf2.adjustByDays(29);
  std::cout<<sf1.getYear()<<std::endl;
  std::cout<<sf2.getYear()<<std::endl;
  if(sf1 == sf2)
    std::cout<<"SFDate: Adjust by Days ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFDate: adjust by days failed"<<std::endl;
  }
  SFDate sf3(sf2);
  if(sf3 == sf2)
    std::cout<<"SFDate: Copy ctor ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFDate: Copy ctor failed"<<std::endl;
  }

  SFDate sf4(sf3);
  sf3++;
  sf3--;
  if(sf3 == sf4)
    std::cout<<"SFDate: Operator ++ -- ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFDate: Operator ++ -- failed"<<std::endl;
  }
  return 0;
}

int SFTestHarness::runTimeTests() {
  int errors = 0;

  SFTime t1(21,21,21);
  SFTime t2(1,21,21);
  t1.adjustByHours(4);
  if(t1 == t2)
    std::cout<<"SFTime: Adjust by hours ok and ctor ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFTime: Adjust by hours failed"<<std::endl;
  }
  SFTime t3(t2);
  if(t3 == t2)
    std::cout<<"SFTime: copy ctor ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFTime copy ctor faield"<<std::endl;
  }


  return 0;
}

int SFTestHarness::runDateTimeTests() {
  int errors = 0;
  SFDateTime sf1;
  char* a = new char[4];
  strcpy(a, "CST");
  SFTimezone stz(a);
  SFDateTime sf2(sf1);
  if( sf1== sf2)
    std::cout<<"SFDateTime: ctor ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFDateTime: ctor failed"<<std::endl;
  }


return 0;

}

int SFTestHarness::runIntervalTests() {
  int errors = 0;
  SFInterval sf1;
  char* a = new char[61];
  strcpy(a,"0 years, 0 months, 0 days, 0 hours, 0 minutes and 0 seconds");


  const char*b = sf1;
  std::cout<<"b: "<<b<<std::endl;
  std::cout<<"a: "<<a<<std::endl;
  if( strcmp(b,a)==0)
    std::cout<<"SFInterval: ctor and conversion operator ok"<<std::endl;
  else
  {
    errors+=1;
    std::cout<<"SFDateTime: ctor and conversion operator failed"<<std::endl;
  }

  return 0;
}

int SFTestHarness::runTimezoneTests() {
  int errors = 0;
  char* a = new char[4];
  strcpy(a,"EST");
  SFTimezone stz1(a);
  SFTimezone stz2(stz1);
  if(strcmp(stz1.getTimezone(),stz2.getTimezone()) == 0)
    std::cout<<"SFTimezone: ctor tests ok"<<std::endl;
  else
      {
        std::cout<<"SFTimezone: ctor tests failed"<<std::endl;
        errors +=1;
      }

  return 0;
}

/*
 * Return string representation of interval between two dates
 * Ex. aDate1 = "02/15/2018"
 *     aDate2 = "02/17/2018"
 * Returns : "0 years, 0 months, 2 days, 0 hours, 0 minutes and 0 seconds"
 */
 std::string SFTestHarness:: dateDifferenceTest(std::string aDate1, std::string aDate2) {
    SFDate d1=SFDate(aDate1.c_str());
    SFDate d2=SFDate(aDate2.c_str());
    const char* a = d2 - d1;
    std::string str = a;
    delete[] a;
    a = nullptr;
    return str;

 }

/*
 * Return string representation of date with weeks adjusted
 * Ex. aDate = "02/15/2018"
 *     aWeeks = 1
 * Returns : "02/22/2018"
 */
std::string SFTestHarness::adjustDateByWeeksTest(std::string aDate, int aWeeks) {
  SFDate d1(aDate.c_str());
  d1.adjustByWeeks(aWeeks);
  std::string str = d1.toDateString();
  return str;
}

/*
 * Return string representation of date with month changed
 * Ex. aDate = "02/15/2018"
 *     aMonth = 5
 * Returns : "05/15/2018"
 */
std::string SFTestHarness::setMonthDateTest(std::string aDate, int aMonth) {
  SFDate d1(aDate.c_str());
  d1. setMonth(aMonth);
  std::string str = d1.toDateString();
  return str;
}

/*
 * Return integer representation of the day of the week for the given date
 * Ex. aDate = "02/15/2018"
 * Returns : 4
 */
int SFTestHarness::getDayOfWeekDateTest(std::string aDate) {
  SFDate d1(aDate.c_str());
  int temp = d1.getDayOfweek();
  return temp;
}

/*
 * Return string representation of date at the end of month of the given date
 * Ex. aDate = "03/15/2018"
 * Returns : "03/31/2018"
 */
std::string SFTestHarness::endOfMonthDateTest(std::string aDate) {
  SFDate d1(aDate.c_str());
  d1.endOfMonth();
  std::string str = d1.toDateString();
  return str;
}

/*
 * Return string representation of interval between two times
 * Ex. aTime1 = "09:05:15"
 *     aTime2 = "09:05:22"
 * Returns : "0 years, 0 months, 0 days, 0 hours, 0 minutes and 7 seconds"
 */
std::string SFTestHarness::timeDifferenceTest(std::string aTime1, std::string aTime2) {
  SFTime t1=SFTime(aTime1.c_str());
  SFTime t2=SFTime(aTime2.c_str());
  const char* a = t2 - t1;
  std::string str = a;
  delete[] a;
  a = nullptr;
  return str;
}

/*
 * Return string representation of interval between two times
 * Ex. aTime1 = "09:05:15"
 *     aMinutes = 5
 * Returns : "09:10:15"
 */
std::string SFTestHarness::adjustTimeByMinutesTest(std::string aTime1, int aMinutes) {
  SFTime t1 = SFTime(aTime1.c_str());
  t1.adjustByMinutes(aMinutes);
  std::string str = t1.toTimeString();

  return str;
}

/*
 * Return minutes from the given time
 * Ex. aTime = "09:05:15"
 * Returns : 5
 */
int SFTestHarness::getMinutesTimeTest(std::string aTime) {
  SFTime t1 = SFTime(aTime.c_str());
  return t1.getMinutes();
}

/*
 * Return string representation of interval between two times
 * Ex. aDateTime1 = "02/15/2018 09:05:15"
 *     aTimeZone1 = "PST"
 *     aDateTime2 = "02/15/2018 11:05:15"
 *     aTimeZone2 = "EST"
 * Returns : "0 years, 0 months, 0 days, 1 hours, 0 minutes and 0 seconds"
 */
std::string SFTestHarness::dataTimeDifferenceTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2) {
    SFTimezone tz1=SFTimezone(aTimezone1.c_str());
    SFDateTime dt1=SFDateTime(aDateTime1.c_str(),&tz1);
    SFTimezone tz2=SFTimezone(aTimezone2.c_str());
    SFDateTime dt2=SFDateTime(aDateTime2.c_str(),&tz2);
    const char* a=dt2-dt1;
    std::string str = a;
    delete[] a;
    a = nullptr;
    return str;
}

/*
 * Return string representation of given date-time
 * Ex. aDateTime = "02/15/2018 09:05:15"
 *     aTimeZone = "PST"
 * Returns : "Feb 15, 2018 09:05:15 PST"
 */
std::string SFTestHarness::dataTimeToStringTest(std::string aDateTime, std::string timezone) {
  SFTimezone tz1=SFTimezone(timezone.c_str());
  SFDateTime dt1=SFDateTime(aDateTime.c_str(),&tz1);
  std::string str = dt1.toDateTimeString();
  return str;
}

/*
 * Return string representation of given GMT date-time converted to given timezone
 * Ex. aDateTime = "02/15/2018 09:05:15"
 *     aTimeZone = "PST"
 * Returns : "Feb 15, 2018 01:05:15 PST"
 */
std::string SFTestHarness::timezoneConversionDateTimeTest(std::string aDateTime, std::string timezone) {
  SFTimezone tz1=SFTimezone(timezone.c_str());
  SFDateTime dt1=SFDateTime(aDateTime.c_str());
  dt1.setTimezone(tz1);
  return dt1.toDateTimeString();
}

/*
 * Return true if aDateTime1 is stricty greater than aDateTime2
 * Ex. aDateTime1 = "02/15/2018 09:05:15"
 *     aTimeZone1 = "PST"
 *     aDateTime2 = "02/15/2018 11:05:15"
 *     aTimeZone2 = "EST"
 * Returns : true
 */
bool SFTestHarness::greaterThanDateTimeTest(std::string aDateTime1, std::string aTimezone1, std::string aDateTime2, std::string aTimezone2) {
  SFTimezone tz1=SFTimezone(aTimezone1.c_str());
  SFDateTime dt1=SFDateTime(aDateTime1.c_str(),&tz1);
  SFTimezone tz2=SFTimezone(aTimezone2.c_str());
  SFDateTime dt2=SFDateTime(aDateTime2.c_str(),&tz2);
  return (tz1>tz2);
}

int SFTestHarness::runAllTests() {
  int theResult = runDateTests();
  theResult+=runTimeTests();
  theResult+=runDateTimeTests();
  theResult+=runIntervalTests();
  theResult+=runTimezoneTests();
  return theResult;
}
