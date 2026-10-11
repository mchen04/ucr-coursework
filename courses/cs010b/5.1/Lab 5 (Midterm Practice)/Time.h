// Time interface file

#ifndef __TIME_H__
#define __TIME_H__

#include <iostream>

using namespace std;

class Time {
 private:
   int _hour;
   int _minute;
   int _second;
   string _ampm;
 public:
   Time(); //initializes time to 00:00:00 (24-hour format)
   Time(int hour, int minute, int second); //24-hour format (09:00:00)
   Time(int hour, int minute, int second, const string &ampm); //12-hour format (9:00:00am)
   
   //Outputs in either 12-hour or 24-hour format depending on value in ampm.
   // You can output leading 0's using setfill and setw.
   // Example, cout << setfill('0') << setw(2) << hour << setw(2) << minute ...
   friend ostream & operator<<(ostream &, const Time &);
 private:
 
   //Fixes time errors in constructors:
   // Hour must be within 0 to 23 for 24-hour format or 1 to 12 for 12-hour format.
   // Minute and second must be within 0 to 59.
   // ampm must be either "am" or "pm" for 12-hour format or "" (empty string) for 24-hour format
   // If ampm not valid, make it "am".
   // If hour, minute, and/or second is invalid fix it to nearest valid value.
   // For example, Time(27, 21, 68) will become 23:21:59
   void init();
};

#endif //__TIME_H__
