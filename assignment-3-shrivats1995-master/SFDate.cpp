//#include"SFDate.hpp"
#include"SFDateTime.hpp"
#include"SFInterval.hpp"
#include<string>
#include<iostream>
#include<ctime>
#include<string.h>
#include<map>
int SFDate::lowM[] = {4, 6, 9, 11};
int SFDate::highM[] = {1, 3, 5, 7, 8, 10, 12};
class SFDateTime;

//mmap[1] = "Jan";
bool checkHighMonth(int month) // check if month has 31 days
{
  int i;
  for(i=0;i<4;i++)
  {
    if(month == SFDate::lowM[i])
      return false;
    else
      return true;
  }
  for(i=0;i<7;i++)
  {
    if(month == SFDate::highM[i])
      return true;
    else
      return false;
  }
}

int SFDate::inc_month() // inc month val
{
  int temp;
  if(month == 12)
    return 1;
  else
  {
    temp = month+ 1;
    return temp;
  }
}

int incr_month(int month)
{
  int temp;
  if(month == 12)
    return 1;
  else
  {
    temp = month+ 1;
    return temp;
  }
}

int decr_month(int month) // dec month val
{
  int temp;
  if(month == 1)
    return 12;
  else
  {
    temp = month - 1;
    return temp;
  }
}

int SFDate::dec_month()
{
  if(month == 1)
    return 12;
  else
  {
    int temp = month- 1;
    return temp;
  }
}


bool SFDate::isLeapYear() // check leap year
{
  if(year%4 == 0)
  {
    if(year%4 == 100)
    {
      if(year%400 == 0)
        return true;
      else
        return false;
    }
    else
      return true;
  }
  else
  {
    return false;
  }
}

bool SFDate:: isNextMonth(){ //for rollover check next month
  if(month == 2)
  {
    if(this->isLeapYear())
    {
      if(day == 29)
        return true;
      else
        return false;
    }
    else
    {
      if(day == 28)
        return true;
      else
        return false;
    }
  }

  else
  {
    if(checkHighMonth(month))
    {
      if(day == 31)
        return true;
      else
        return false;

    }

    else
    {
      if(day == 30)
        return true;
      else
        return false;
    }
  }
}

bool SFDate:: isPrevMonth() // check for rollover
{
  if(day ==1)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SFDate::isNextYear()
{
  if(month == 12)
    return true;
  else
    return false;
}

bool SFDate::isPrevYear()
{
  if(month == 1)
    return true;
  else
    return false;
}

int SFDate::prevMonth()
{
  if(month == 1)
  {
    return 12;
  }
  else
  {

    int temp = month-1;
    std::cout<<"func temp is: "<<temp<<std::endl;
    return temp;
  }
}

int SFDate::nextMonth()
{
  if(month == 12)
    return 1;
  else
  {
    int temp = month + 1;
    return temp;
  }
}



int SFDate::num_days(int month) // get num of days in month
{
  if(month ==2)
  {
    if(isLeapYear())
      return 29;
    else
      return 28;
  }
  else if(checkHighMonth(month) )
  {
  //  std::cout<<"num_days :"<<31<<std::endl;
    return 31;
  }
  else
  {
    //std::cout<<"num_days :"<<30<<std::endl;
    return 30;
  }
}

bool SFDate:: isValidDay(int aDay) // check for valid day, mont han year
{
  if(aDay > 0 && aDay<= num_days(month))
    return true;
  else
    return false;
}

bool SFDate:: isValidMonth(int aMonth)
{
  if(aMonth< 1 || aMonth>12 )
    return false;
  else
    return true;
}

bool SFDate:: isValidYear(int aYear)
{
  if(aYear < 0 || aYear> 9999)
    return false;
  else
    return true;
}


SFDate:: SFDate() // default ctor
{
  time_t curr = time(0);
  struct tm  currT = *localtime(&curr);
  year = currT.tm_year + 1900;
  month = currT.tm_mon + 1;
  day = currT.tm_mday;


}

SFDate:: SFDate(const char *aDateTimeString)   // paramterized ctor
{
  char* temp = new char[5];
  month = atoi(strncpy(temp, aDateTimeString, 2));
  day = atoi(strncpy(temp, aDateTimeString +3, 2));
  year = atoi(strncpy(temp, aDateTimeString+6, 4));
  delete[] temp;
  temp = nullptr;
  //std::cout<<year<<day<<month<<std::endl;
}

SFDate:: SFDate(int month, int day, int year)
{
  this->month = month;
  this->day = day;
  this->year = year;
}

SFDate:: SFDate(const SFDate &aCopy) // copy ctor
{
  month = aCopy.month;
  day = aCopy.day;
  year = aCopy.year;
}

SFDate:: SFDate(const SFDateTime &aCopy)
{
  month = aCopy.month;
  day = aCopy.day;
  year = aCopy.year;
}


SFDate&  SFDate:: operator ++(int)  //inc day
{

  if(isNextMonth())
  {
    if(isNextYear())
    {
      day = 1;
      year = year + 1;
      month = this->inc_month();

    }
    else
    {
      day = 1;
      month = this->inc_month();
    }
  }
  else
  {
    day = day + 1;
  }
  return *this;
}

SFDate& SFDate:: operator --(int) // dec day
{
  if(isPrevMonth())
  {
    if(isPrevYear())
    {
      day = 31;
      year --;
      month = 12;
    }
    else
    {
      std::cout<<"Entered else"<<std::endl;
      int temp = prevMonth();
      std::cout<<"temp: "<<temp<<std::endl;
      if(temp == 2)
      {
        std::cout<<"Entered isprev month"<<std::endl;
        if(isLeapYear())
        {
          month = this->dec_month();
          day = 29;
        }
        else
        {
          month = this->dec_month();
          day = 28;
        }
      }

      else if (checkHighMonth(prevMonth()))
      {
        day = 31;
        month = this->dec_month();
      }
      else
      {
        day = 30;
        month = this->dec_month();
      }
    }

  }
  else
  {
    day = day - 1;
  }
  return *this;
}

SFDate& SFDate:: adjustByDays(int n) // inc/dec by n days
{
  if(n >=0)
  {
    while ((n + day) > num_days(month))
     {

       n = n - num_days(month);
       if (month == 12)
       {
         month = 1;
         year++;
       }
       else
       {
         month++;

       }
     }
     day +=n;
  }
  else
  {
    n = n*-1;
    while((n + day) > num_days(prevMonth()))
    {
      n = n - num_days(prevMonth());
      if(month == 1)
      {
        month = 12;
        year--;
      }
      else
      {
        month--;
      }
    }
    if(n > day)
    {
      int temp = n - day;
      if(prevMonth() == 2)
      {
        if(isLeapYear())
          day = 29 - temp;
        else
          day = 28- temp;
        month = dec_month();
      }
      else if (checkHighMonth(prevMonth()))
      {
        day = 31 - temp;
        month = dec_month();
      }
      else
      {
        day = 30 - temp;
        month  = dec_month();
      }

    }
    else
    {
      day -= n;

    }
  }
   return *this;
}

SFDate& SFDate:: adjustByWeeks(int n)
{
  int temp = n*7;
  this->adjustByDays(temp);
  return *this;
}

SFDate& SFDate:: adjustByMonths(int n)
{
  int tempM = month;
  if(n>=0)
  {
    for(int i = 0;i<n;i++)
    {
      if(tempM ==2)
      {
        if(isLeapYear())
          this->adjustByDays(29);
        else
          this->adjustByDays(28);
      }
      else if(checkHighMonth(tempM))
      {
        this->adjustByDays(31);
      }
      else
      {
        this->adjustByDays(30);
      }

      tempM = incr_month(tempM);
    }
  }

  else
  {
    n*=-1;
    for (int i = 0;i<n;i++)
    {
      if(tempM ==2)
      {
        if(isLeapYear())
          this->adjustByDays(-29);
        else
          this->adjustByDays(-28);
      }
      else if(checkHighMonth(tempM))
      {
        this->adjustByDays(-31);
      }
      else
      {
        this->adjustByDays(-30);
      }
      tempM = decr_month(tempM);
    }
  }

  return *this;
}

SFDate& SFDate:: adjustByYears(int n)
{
  if(n>=0)
  {
    for(int i = 0;i < n;i ++)
    {
      if(isLeapYear())
        this->adjustByDays(366);
      else
        this->adjustByDays(365);

    }
  }
  else
  {
    n*=-1;
    for(int i = 0;i < n;i ++)
    {
      if(isLeapYear())
        this->adjustByDays(-366);
      else
        this->adjustByDays(-365);

    }
  }
  return *this;
}

//set day, month and year functions

SFDate& SFDate:: setDay(int aDay)
{
  if(isValidDay(aDay))
    this->day = aDay;
  else
  {
    std::cerr<<"Invalid day provided"<<std::endl;
  }
  return *this;
}

SFDate& SFDate:: setMonth(int aMonth)
{
  if(isValidMonth(aMonth))
    this->month = aMonth;
  else
  {
    std::cerr<<"Invalid month provided"<<std::endl;
  }
  return *this;
}

SFDate& SFDate:: setYear(int aYear)
{
  if(isValidYear(aYear))
    this->year = aYear;
  else
  {
    std::cerr<<"Invalid year provided"<<std::endl;
  }
  return *this;
}

//get functions

int SFDate:: getDay()
{
  return day;
}

int SFDate:: getMonth()
{
  return month;
}

int SFDate:: getYear()
{
  return year;
}

int  SFDate:: getDayOfYear()
{
  int temp = 0;
  for(int i = 1;i<month;i++)
  {

    temp += num_days(i);
    //std::cout<<"temp: "<<temp<<std::endl;
  }
  temp = temp + day;
  return temp;
}

int SFDate:: getWeekOfYear()
{
  int temp = getDayOfYear();
  std::cout<<"temp: "<<temp<<std::endl;
  temp = temp/7;
  return (temp+1);
}

int SFDate:: getDayOfweek()
{
  int temp = getDayOfYear()%7;
  return (temp);
}

int SFDate:: daysInMonth()
{
  return num_days(month);
}

SFDate& SFDate:: startOfMonth()
{
  day = 1;
  return *this;
}

SFDate& SFDate:: endOfMonth()
{
  day = num_days(month);
  return *this;
}

SFDate& SFDate:: startOfYear()
{
  day = 1;
  month = 1;
  return *this;
}

SFDate& SFDate:: endOfYear()
{
  day = 31;
  month = 12;
  return *this;
}


//convert to a string
std::string SFDate:: toDateString()
{
  std::string str;

  if(month<10)
  {
    str +="0";
    str +=std::to_string(month);

  }
  else
  {
    str += std::to_string(month);
  }

  str +="/";

  if(day<10)
  {
    str +="0";
    str += std::to_string(day);
  }
  else
  {
    str += std::to_string(day);
  }

  str+="/";

  int count = 0; int temp1 = year;
  while(temp1 != 0)
  {
    temp1 = temp1/10;
    count++;
  }
  count = 4 - count;

  for(int i=0;i<count;i++)
    {
      str += "0";
    }
    str+= std::to_string(year);


  return str;
}


//compare function
int SFDate:: relat_date(SFDate aVal)
{
  if(this->year > aVal.year)
    return 1;
  else if (this->year < aVal.year)
    return -1;
  else
  {

    if(this->month > aVal.month)
      return 1;
    else if (this->month < aVal.month)
      return -1;
    else
    {

      if(this->day > aVal.day)
        return 1;
      else if(this->day < aVal.day)
        return -1;
      else
        return 0;
    }
  }
}
//relational operators

bool SFDate:: operator<(const SFDate &aVal)
{
  int temp = relat_date(aVal);
  if(temp == -1)
    return true;
  else
    return false;

}

bool SFDate:: operator>(const SFDate &aVal)
{
  int temp = relat_date(aVal);
  if(temp == 1)
    return true;
  else
    return false;

}

bool SFDate:: operator<=(const SFDate &aVal)
{
  int temp = relat_date(aVal);
  if(temp == -1 || temp == 0)
    return true;
  else
    return false;

}

bool SFDate:: operator>=(const SFDate &aVal)
{
  int temp = relat_date(aVal);
  if(temp == 1 || temp == 0)
    return true;
  else
    return false;

}

bool SFDate:: operator==(const SFDate &aVal)
{
  int temp = relat_date(aVal);

  if(temp == 0)
    return true;
  else
    return false;

}

bool SFDate:: operator!=(const SFDate &aVal)
{
  int temp = relat_date(aVal);
  if(temp == 0)
    return false;
  else
    return false;

}



bool isLp(int year)
{
  if(year%4 == 0)
  {
    if(year%4 == 100)
    {
      if(year%400 == 0)
        return true;
      else
        return false;
    }
    else
      return true;
  }
  else
  {
    return false;
  }
}

int num_day(int month, int year)
{
  if(month ==2)
  {
    if(isLp(year))
      return 29;
    else
      return 28;
  }
  else if(checkHighMonth(month) )
  {
  //  std::cout<<"num_days :"<<31<<std::endl;
    return 31;
  }
  else
  {
    //std::cout<<"num_days :"<<30<<std::endl;
    return 30;
  }
}



int count_leap(int year)
{
  int count = 0;
  for(int i=0;i<=year;i++)
  {
    if(isLp(i))
      count++;
  }
  return count;
}


int SFDate:: count_days() const
{
  int total, temp;
  total = this->year* 365;
  temp = count_leap(this->year);
  total = total + temp;
  temp = month;
  for(int i = 1;i<this->month;i++)
  {
    total+=num_day(temp, this->year);
    temp++;
  }
  total += this->day;
}

// operator -

SFInterval SFDate:: operator-(const SFDate &other) const
{
  //int temp1 = this->count_days();
  //int temp2 = other.count_days();

  int yrs = 0, mons = 0, days = 0;
  yrs = this->year - other.year;

  if(this->month < other.month)
  {
    yrs = yrs - 1;
    mons = 12 + (this->month - other.month);
  }

  else
    mons = this->month - other.month;

  if(this->day < other.day)
  {
    if(this->month ==1 )
    {
    days = num_day(12, year) + (this->day - other.day);
    mons = mons - 1;
    }
    else
    {
      days = num_day((this->month) - 1, year) + (this->day - other.day);
      mons = mons - 1;
    }
  }
  else
  {

    days = this->day - other.day;
  }
  SFInterval temp;
  temp.years = yrs;
  temp.months = mons;
  temp.days = days;
  return temp;
}

SFInterval SFDate:: operator-(const SFDateTime &other) const
{
  SFDate tempsfdate(other.month, other.day, other.year);
  SFInterval ret;
  ret = *this - tempsfdate;
  return ret;
}


/*
int main()
{
  const char* a = "01/01/0995";
  SFDate sd1(a);
  std::cout<<"day: "<<sd1.getDay()<<std::endl;
  std::cout<<"Month: "<<sd1.getMonth()<<std::endl;
  std::cout<<"Year: "<<sd1.getYear()<<std::endl;

  sd1.adjustByMonths(3);

  std::cout<<"day: "<<sd1.getDay()<<std::endl;
  std::cout<<"Month: "<<sd1.getMonth()<<std::endl;
  std::cout<<"Year: "<<sd1.getYear()<<std::endl;
}
*/
