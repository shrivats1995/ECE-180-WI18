
#ifndef SFInterval_hpp
#define SFInterval_hpp
class SFInterval {
public:
  SFInterval();
  SFInterval(int year, int month, int day, int hours, int minutes, int seconds);
  void setIntVal(int year, int month, int day, int hours, int minutes, int seconds);
  operator const char*(); // Returns the interval of the form "Y years, M months, D days, H hours, M minutes and S seconds"
                          // Ex. 5 years, 3 months, 2 days, 6 hours, 7 minutes and 10 seconds

  int years;
  int months;
  int days;
  int hours;
  int minutes;
  int seconds;
};


#endif /* SFInterval_hpp */
