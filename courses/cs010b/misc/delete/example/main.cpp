#include <iostream>
#include <string>
using namespace std;

int main()
{
    string input;
    cout << "What's your name?" << endl;
    getline(cin, input);
    cout << "Hello " << input << '!' << endl;
}