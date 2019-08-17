#include"SFTimezone.hpp"
#include<string.h>
#include<memory>
#include<iostream>

//default ctor
SFTimezone:: SFTimezone() // default ctor
{
  tz = new char[4];
  strcpy(tz,"GMT");

}

SFTimezone:: SFTimezone(const char* aTimezoneAbbrev) // paramterized ctor
{
  tz = new char[4];
  strcpy(tz, aTimezoneAbbrev);
  std::cout << "tz: " << tz << std::endl;
}

SFTimezone:: SFTimezone(const SFTimezone &aTimezone) // copy ctor
{
  tz = new char[4];
  strcpy(tz, aTimezone.tz);
}

SFTimezone:: operator const char*() // conversion operator
{
   std::unique_ptr<SFTimezone> ptr (new SFTimezone(*this));
   return ptr->tz;
}

void SFTimezone:: setTz(const char* atz)
{
	strcpy(this->tz, atz);
}

char* SFTimezone::getTimezone()
{
	std::unique_ptr<SFTimezone> ptr(new SFTimezone(*this));
	return ptr->tz;
}
