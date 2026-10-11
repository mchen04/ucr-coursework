// Time class test harness - midterm

#include <iostream>
#include "Time.h"

using namespace std;

int main() {
   
/* Uncomment out statements as you implement the necessary member function(s) for that statement. */

   Time t1;
   // Time t2 = Time(13, 12, 33);
   // Time t3 = Time(4, 8, 14, "pm");
   // Time t4 = Time(9, 13, 0, "am");

   cout << endl << "Default Time: " << endl;
   cout << t1 << endl;
   // cout << endl << "24 Hour Time Format: " << endl;
   // cout << t2 << endl;
   // cout << endl << "12 Hour Time Format (pm): " << endl;
   // cout << t3 << endl;
   // cout << endl << "12 Hour Time Format (am): " << endl;
   // cout << t4 << endl;
   // cout << endl;
   
   //Do not put newline at end of time output in operator<< function.
   
   // cout << "Multiple Times on one line:" << endl;
   // cout << t1 << "\t" << t2 << endl;
   
   return 0;
}
