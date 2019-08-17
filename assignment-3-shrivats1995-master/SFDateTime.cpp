#include"SFDateTime.hpp"
#include<iostream>
#include<time.h>
#include<string.h>
#include<cstring>
#include<map>
#include<memory>
#include<map>
#include"SFInterval.hpp"
std::map<int, std::string> mmap = {{1, "January"},{2, "February"},{3, "Mar"},{4, "April"},{5, "May"},{6, "June"},{7, "July"},{8, "August"},{9, "September"},
{10, "October"}, {11, "November"}, {12, "December"}};

void SFDateTime:: parseDateTime(const char* aString)
{
	std::cout << "string: "<<(aString) << std::endl;
	char* temp = new char[5];
	this->month = atoi(strncpy(temp, aString, 2));

	this->day = atoi(strncpy(temp, aString + 3, 2));

	this->year = atoi(strncpy(temp, aString + 6, 4));

	this->hours = atoi(strncpy(temp, aString + 12, 2));

	this->minutes = atoi(strncpy(temp, aString + 15, 2));

	this->seconds = atoi(strcpy(temp, aString + 17));

	//std::cout<<"seconds: "<< temp << std::endl;

}



SFDateTime:: SFDateTime(SFTimezone *aTimezone)
{
	//std::cout<<"timezone:" << aTimezone->tz << std::endl;
	if (aTimezone == nullptr || strcmp(aTimezone->getTimezone(), "GMT") == 0)
	{
		time_t rawtime;
		struct tm * gtm;
		time(&rawtime);
		gtm = gmtime(&rawtime);

		this->hours = gtm -> tm_hour ;

		this->minutes = gtm->tm_min;
		this->seconds = gtm->tm_sec;
		this->year = gtm->tm_year + 1900;
		this->month = gtm->tm_mon + 1;
		this->day = gtm->tm_mday;
		strcpy(this->tz, "GMT");
		std::cout<<"this tzdef: " << this->tz << std::endl;
	}
	else
	{
		std::cout << "entered else" << std:: endl;
		time_t curr = time(0);
		struct tm  currT = *localtime(&curr);
		this->year = currT.tm_year + 1900;
		this->month = currT.tm_mon + 1;
		this->day = currT.tm_mday;
		this->minutes = currT.tm_min;
		this->seconds = currT.tm_sec;
		this->hours = currT.tm_hour;
		strcpy(this->tz, aTimezone->getTimezone());

		if (strcmp(this->tz, "PST") == 0)
		{
			this->hours = currT.tm_hour;
		}
		else if (strcmp(aTimezone->getTimezone(), "EST") == 0)
		{
			this->adjustByHours(3);
		}
		else if (strcmp(aTimezone->getTimezone(), "CST") == 0)
		{
			this->adjustByHours(2);
		}

	}
}

SFDateTime::SFDateTime(const SFDateTime &aCopy)
{
	if (&aCopy != nullptr)
	{
		this->hours = aCopy.hours;
		this->minutes = aCopy.minutes;
		this->seconds = aCopy.seconds;
		this->year = aCopy.year;
		this->month = aCopy.month;
		this->day = aCopy.day;
		this->tz = aCopy.tz;
	}
}

SFDateTime::SFDateTime(int aMonth, int aDay, int aYear, int anHour , int aMinutes , int aSeconds, SFTimezone *aTimezone)
{
	this->hours = anHour;
	this->minutes = aMinutes;
	this->seconds = aSeconds;
	this->year = aYear;
	this->month = aMonth;
	this->day = aDay;
	if (aTimezone == nullptr)
		this->setTz("GMT");
	else
		this->tz = aTimezone->getTimezone();
}

SFDateTime:: SFDateTime(const char* aString, SFTimezone *aTimezone)
{
	this->parseDateTime(aString);
	if (aTimezone == nullptr)
		this->setTz("GMT");
	else
		this->tz = aTimezone->getTimezone();

}

SFDateTime:: SFDateTime(const SFDate &aDate, const SFTime &aTime, SFTimezone *aTimezone)
{
	SFDate dt(aDate);
	SFTime tm(aTime);
	if(aTimezone == nullptr)
	{
		this->setTz("GMT");
	}
	else
	{
		this->tz = aTimezone->getTimezone();
	}
	this->hours = tm.getHour();
	this->minutes = tm.getMinutes() ;
	this->seconds = tm.getSeconds();
	this->year = dt.getYear();
	this->month = dt.getMonth();
	this->day = dt.getDay();
}



SFTimezone& SFDateTime:: getTimezone()
{
	SFTimezone temp;;
	temp.setTz(this->tz);
	return temp;
}

SFDateTime&  SFDateTime:: setTimezone(SFTimezone &aTimezone)
{
	this->tz = aTimezone.getTimezone();
	return *this;
}
//convert to string
std::string SFDateTime:: toDateTimeString()
{
	std::map<int, std::string>::iterator iter = mmap.begin();
	/*while(iter != mapOfWords.end())
	{
		std::cout<<iter->first<<" :: "<<iter->second<<std::endl;
		iter++;
	}*/

	std::string str;
	std::string temp;
	temp = mmap[this->month];
	temp = temp.substr(0,3);
	str+=temp;
	str+=" ";
	str+=std::to_string(this->day);
	str+= ", ";
	int count = 0; int temp1 = this->year;
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
  str+= std::to_string(this->year);
	str+= " ";
	if(this->hours<10)
  {
    str +="0";
    str +=std::to_string(this->hours);

  }
  else
  {
    str += std::to_string(this->hours);
  }

  str +=":";

  if(this->minutes<10)
  {
    str +="0";
    str += std::to_string(this->minutes);
  }
  else
  {
    str += std::to_string(this->minutes);
  }

  str+=":";

  if(this->seconds<10)
  {
    str +="0";
    str +=std::to_string(this->seconds);

  }
  else
	{
    str += std::to_string(this->seconds);
  }
	str += " ";
	str += (this->tz);
	return str;
}
//conversion operator
SFDateTime:: operator const char*()
{
	std::string str = this->toDateTimeString();
	char* a = new char[str.length() + 1];
	strcpy(a, str.c_str());
	std::unique_ptr< char*> ptr (new  char*(a));

	return *ptr;
}

SFDateTime:: operator SFDate()
{
	SFDate ret(*this);
	return ret;
}

// relational operators

std::map<std::string, int> timezones = {{"GMT", 1} , {"EST", 2}, {"CST", 3},{"PST", 4}};

int SFDateTime:: relat_datetime(SFDateTime aVal)
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
			      {
							if(timezones[this->tz] > timezones[aVal.tz])
								return 1;
							else if(timezones[this->tz] < timezones[aVal.tz])
								return -1;
							else
									return 0;

						}
					}

				}
			}
		}
	}


}

bool SFDateTime:: operator<(const SFDateTime &aVal)
{
  int temp = relat_datetime(aVal);
  if(temp == -1)
    return true;
  else
    return false;

}

bool SFDateTime:: operator>(const SFDateTime &aVal)
{
  int temp = relat_datetime(aVal);
  if(temp == 1)
    return true;
  else
    return false;

}

bool SFDateTime:: operator<=(const SFDateTime &aVal)
{
  int temp = relat_datetime(aVal);
  if(temp == -1 || temp == 0)
    return true;
  else
    return false;

}

bool SFDateTime:: operator>=(const SFDateTime &aVal)
{
  int temp = relat_datetime(aVal);
  if(temp == 1 || temp == 0)
    return true;
  else
    return false;

}

bool SFDateTime:: operator==(const SFDateTime &aVal)
{
  int temp = relat_datetime(aVal);
  if(temp == 0)
    return true;
  else
    return false;

}

bool SFDateTime:: operator!=(const SFDateTime &aVal)
{
  int temp = relat_datetime(aVal);
  if(temp == 0)
    return false;
  else
    return false;

}

SFInterval SFDateTime:: operator-(const SFDateTime &other) const
{

}

/*
int main()
{
	char* a = new char[4];
	strcpy(a, "CST");
	SFTimezone stz(a);
	std::cout << "timezonemain:" << stz.getTimezone() << std::endl;
	char* b = new char[20];
	strcpy(b, "09/27/1995 09:07:34");
	SFDate d1(3, 29, 2018);
	SFDateTime sk(stz);
	SFDateTime sk2(sk);
	std::cout<<sk2.getTimezone()<<std::endl;
	std::cout<<sk.getTimezone()<<std::endl;
	SFInterval si;

	si  = d1 - sk;
	std::cout<<"hello"<<std::endl;
	const char* c = si;
	std::cout<<c<<std::endl;
	//std::cout << sf.getMonth() << "/" << sf.getDay() << "/" << sf.getYear() << " " << sf.getHour() << ":" << sf.getMinutes() << ":" << sf.getSeconds() << std::endl;
	return 0;
}*/
