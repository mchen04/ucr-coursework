#include <iostream>
#include <string>

using namespace std;

void flipString(string &s){
    if ( s.size() <= 1 ){
      return ;
    }

    string r = s.substr( 1, s.size() - 2 );

   flipString( r );

   s = s.substr( s.size() - 1 ) + r + s[0] ;
}

int main() {
   string line;
   cout << "Enter a sentence:" << endl;
   getline(cin, line);
   cout << endl;
   cout << line << endl;
   flipString(line);
   cout << line << endl;

   return 0;
}



