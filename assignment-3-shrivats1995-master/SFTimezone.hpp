#ifndef SFTimezone_hpp
#define SFTimezone_hpp
class SFTimezone {
public:
  
  SFTimezone();
  SFTimezone(const char* aTimezoneAbbrev); //GMT, EST, CST, PST
  SFTimezone(const SFTimezone &aTimezone);

  operator const char*(); // Returns the 3 letter abbreviation of the timezone object

  void setTz(const char* atz);
  char* getTimezone();

protected:
  char* tz;
};



#endif /* SFTimezone_hpp */
