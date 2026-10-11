#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

// Place charCnt prototype (declaration) here
int charCnt(string filename, char ch) ;

int main() {
   string filename;
   char ch;
   int chCnt = 0;
   
   cout << "Enter the name of the input file: ";
   cin >> filename;
   cout << endl;
   cout << "Enter a character: ";
   cin.ignore(); // ignores newline left in stream after previous input statement
   cin.get(ch);
   cout << endl;

   chCnt = charCnt(filename, ch);   
   cout << "# of " << ch << "'s: " << chCnt << endl;
   
   return 0;
}

int charCnt(string filename, char ch) {
   string line ;
   int total_count = 0 ;

   ifstream inFS;
   
   inFS.open(filename) ;

   if (!inFS.is_open()){
      cout << "Error opening " << filename << endl ;
      exit (1) ;  
   }

   else{
      while (getline(inFS, line)){
         for (unsigned int i = 0; i < line.size(); i++ ){
            if ( line[i] == ch){
               total_count ++ ;
            }
         }
      }   
   }

   inFS.close() ;
   return total_count ;


}
// Place charCnt implementation here
