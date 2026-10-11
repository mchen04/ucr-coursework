// Time class implementation file

#include "Time.h"

#include <iomanip> // library needed for setfill and setw

Time::Time() {
    _hour = 0 ;
    _minute = 0 ;
    _second = 0 ;
    _ampm = "" ;
}

Time::Time(int hour, int minute, int second){
    _hour = hour ;
    _minute = minute ;
    _second = second ;
    _ampm = "" ;
}

Time::Time(int hour, int minute, int second, const string &ampm){
    _hour = hour ;
    _minute = minute ;
    _second = second ;
    _appm = ampm ;
}

osteam & operator<<( ostream & o, const Time &){
    cout << setfill('0') << setw(2) << Time._hour << ":" << setfill('0') << setw(2) << Time._minute << ":" << setfill('0') << setw(2) << Time._second << endl ;
}

void init(){
    if (_ hour < 0) {
        _hour = 0 ;
    }
    if (_minute > 59) {
        _minute = 59 ;
    }
    if (_minute < 0) {
        _minute = 0 ;
        }
    if (_second > 59) {
        _second = 59 ;
    }
    if (_second < 0) {
        _second = 0 ;
    }
    if ( _hour > 23 ){
        _hour = 23 ;
    }

    if (_ampm != ""){
        if (_ampm != "am" && _ampm != "pm"){
            _ampm = "am" ;
        }
        if (_hour > 12) {
            _hour = 12 ;
        }
    }
}