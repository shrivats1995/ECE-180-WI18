//#include"SFTime.hpp"
#include"SFDateTime.hpp"
#include<ctime>
#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
#include"SFInterval.hpp"
// inc minutes with rollover

int SFTime:: inc_minutes(int val, bool flag)
{

  if( val + minutes > 59)
  {

    hours = hours + 1;
    int temp = 60 - minutes;
    if(flag == 0)
    {

      return (val - temp);
    }
    else
    {

      return (val - temp - 1);
    }
  }
  else
  {
    if(flag == false)
      return(minutes + val);
    else
      return (minutes + val - 1);
  }
}

int SFTime:: dec_minutes(int val, bool flag)
{
  if((minutes - val) >= 0)
    return (minutes - val);
  else
  {
    hours = hours - 1;
    return (60 - (val - minutes));
  }
}

//check rollover conditions
bool SFTime:: checkPosRollover(int h, int m, int s)
{
  int temp1 = hours * 3600 + minutes * 60 + seconds;
  int temp2 = h * 3600 + m * 60 + s;
  int temp = 86400;
  if(temp1 + temp2 >= temp)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SFTime:: checkNegRollover(int h, int m, int s)
{
  int temp1 = hours * 3600 + minutes * 60 + seconds;
  int temp2 = h * 3600 + m * 60 + s;
  if(temp1 - temp2 < 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int eqSecs(int h, int m, int s)
{
  return ((h * 3600) +(m * 60) + s );
}

int eqMins(int h,int m, int s)
{
  return ((h * 60) + m + s/60);
}

int eqHours(int h,int m, int s)
{
  return ((h ) + (m/60) + s/3600);
}

//default ctor

SFTime:: SFTime()
{
  time_t curr = time(0);
  struct tm  currT = *localtime(&curr);
  hours = currT.tm_hour;
  minutes = currT.tm_min;
  seconds = currT.tm_sec;
//  std::cout<<hours<<" "<<minutes<<" "<<seconds<<std::endl;
}

SFTime:: SFTime(const char *aTimeString)
{
  char* temp = new char[3];
  hours = atoi(strncpy(temp, aTimeString, 2));
  minutes = atoi(strncpy(temp, aTimeString +3, 2));
  seconds = atoi(strncpy(temp, aTimeString+6, 2));
  delete[] temp;
  temp = nullptr;
//  std::cout<<hours<<" "<<minutes<<" "<<seconds<<std::endl;
}

SFTime:: SFTime(int anHour, int aMinutes, int aSeconds)
{
  hours = anHour;
  minutes = aMinutes;
  seconds = aSeconds;
}
//copy ctor
SFTime:: SFTime(const SFTime &aCopy)
{
  hours = aCopy.hours;
  minutes = aCopy.minutes;
  seconds = aCopy.seconds;
}


SFTime:: SFTime(const SFDateTime &aCopy)
{
  hours = aCopy.hours;
  minutes = aCopy.minutes;
  seconds = aCopy.seconds;
}

//adjust by minute and hours
//check rollover and calculate

SFTime& SFTime:: adjustByMinutes(int n)
{
  bool flag = false;
  int temp =0;
  if(n>=0)
  {
    while(checkPosRollover(0, n, 0))
    {
      n = n - eqMins(0, 0, 86400 - eqSecs(hours, minutes, 0));
      flag = true;
      hours = 0;
      minutes = 0;
    }

    temp = n/60;
    hours = hours + temp;
    temp = n%60;
    minutes = inc_minutes(temp, false);
    return *this;
  }
  else if (n< 0)
  {

    n = n * -1;
    while(checkNegRollover(0, n, 0))
    {
      n = n - eqMins(0, 0, eqSecs(hours, minutes, 0) - 0);
      flag = true;
      hours = 23;
      minutes = 60;
    }
    temp = n/60;
    hours = hours - temp;
    temp = n%60;
    minutes = dec_minutes(temp, false);
    return *this;
  }
  return *this;
}

SFTime& SFTime:: adjustByHours(int n)
{
  if(n >=0)
  {
    while(checkPosRollover(n, 0, 0))
    {
      n = n - eqHours(0, 0, 86400 - eqSecs(hours, 0, 0));
      hours =0;
    }
    hours = hours + n;
    return *this;
  }

  else
  {
    n = n * -1;
    while(checkNegRollover(n,0,0))
    {
      n = n - eqHours(0, 0, eqSecs(hours, 0, 0) - 0);
      hours = 24;
    }
    hours = hours - n;
    return *this;
  }
}

// - operator
SFInterval SFTime:: operator-(const SFTime &other) const
{
  SFTime st(other);
  SFInterval itvl;
  int hrs, mins, secs;
  mins = this->minutes;
  hrs = this->hours;
  secs = this->seconds;
  if(st.seconds > secs)
    {
        --mins;
        secs+=60;
    }

    itvl.seconds = secs - st.getSeconds();
    if(st.minutes > mins)
    {
        --hrs;
        mins += 60;
    }
    itvl.minutes = mins - st.minutes;
    itvl.hours = hrs - st.hours;
    return itvl;
}

SFInterval SFTime:: operator-(const SFDateTime &other) const
{
  SFTime st(other);
  SFInterval itvl;
  int hrs, mins, secs;
  mins = this->minutes;
  hrs = this->hours;
  secs = this->seconds;
  if(st.seconds > secs)
    {
        --mins;
        secs+=60;
    }

    itvl.seconds = secs - st.getSeconds();
    if(st.minutes > mins)
    {
        --hrs;
        mins += 60;
    }
    itvl.minutes = mins - st.minutes;
    itvl.hours = hrs - st.hours;
    return itvl;
}


int  SFTime:: getHour()
{
  return hours;
}

int SFTime::  getMinutes()
{
  return minutes;
}
int SFTime:: getSeconds()
{
  return seconds;
}

SFTime& SFTime:: startOfDay()
{
  hours =0;
  minutes =0;
  seconds = 0;
  return *this;
}

SFTime& SFTime:: endOfDay()
{
  hours = 23;
  minutes = 59;
  seconds = 59;
  return *this;
}

std::string SFTime:: toTimeString()
{
  std::string str;

  if(hours<10)
  {
    str +="0";
    str +=std::to_string(hours);

  }
  else
  {
    str += std::to_string(hours);
  }

  str +=":";

  if(minutes<10)
  {
    str +="0";
    str += std::to_string(minutes);
  }
  else
  {
    str += std::to_string(minutes);
  }

  str+=":";

  if(seconds<10)
  {
    str +="0";
    str +=std::to_string(seconds);

  }
  else
  {
    str += std::to_string(seconds);
  }

  return str;
}
//relational operator

int SFTime:: relat_time(SFTime aVal)
{
  if(this->hours > aVal.hours)
    return 1;
  else if (this->hours < aVal.hours)
    return -1;
  else
  {
    if(this->minutes > aVal.minutes)
      return 1;
    else if (this->minutes < aVal.minutes)
      return -1;
    else
    {
      if(this->seconds > aVal.seconds)
        return 1;
      else if(this->seconds < aVal.seconds)
        return -1;
      else
        return 0;
    }
  }
}


bool SFTime:: operator<(const SFTime &aVal)
{
  int temp = relat_time(aVal);
  if(temp == -1)
    return true;
  else
    return false;

}

bool SFTime:: operator>(const SFTime &aVal)
{
  int temp = relat_time(aVal);
  if(temp == 1)
    return true;
  else
    return false;

}

bool SFTime:: operator<=(const SFTime &aVal)
{
  int temp = relat_time(aVal);
  if(temp == -1 || temp == 0)
    return true;
  else
    return false;

}

bool SFTime:: operator>=(const SFTime &aVal)
{
  int temp = relat_time(aVal);
  if(temp == 1 || temp == 0)
    return true;
  else
    return false;

}

bool SFTime:: operator==(const SFTime &aVal)
{
  int temp = relat_time(aVal);
  if(temp == 0)
    return true;
  else
    return false;

}

bool SFTime:: operator!=(const SFTime &aVal)
{
  int temp = relat_time(aVal);
  if(temp == 0)
    return false;
  else
    return false;

}

/*
int main()
{
  SFTime sft("00:22:44");
  std::cout<<"hours: "<<sft.getHour()<<std::endl;
  std::cout<<"Mins: "<<sft.getMinutes()<<std::endl;
  std::cout<<"secs: "<<sft.getSeconds()<<std::endl;

  sft.adjustByHours(-1);
  std::cout<<"hours: "<<sft.getHour()<<std::endl;
  std::cout<<"Mins: "<<sft.getMinutes()<<std::endl;
  std::cout<<"secs: "<<sft.getSeconds()<<std::endl;
}
*/
