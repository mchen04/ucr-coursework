#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readData(const string &, vector<double> &, vector<double> &);
double interpolation(double, const vector<double> &, const vector<double> &);
bool isOrdered(const vector<double> &);
void reorder(vector<double> &, vector<double> &);
bool inRange(double, const vector<double> &) ;
int same_value_index (double , const vector<double> &, const vector<double> &) ;

int main(int argc, char *argv[]) 
{

    string inputFile;
    string outputFile;
   
    inputFile = argv[1];

    vector<double> flight_angle, lift_coefficient ;
    double user_flight_angle ;
    string user_input ;
    
    ifstream inFS ;
    inFS.open(inputFile) ;

    readData(inputFile, flight_angle, lift_coefficient) ;
    reorder(flight_angle, lift_coefficient);

    cout << "What is your flight angle path?" << endl ;
    cin >> user_flight_angle ;

    if (inRange (user_flight_angle, flight_angle)) 
    {

        if (same_value_index(user_flight_angle, flight_angle, lift_coefficient) != 0 )
        {

            cout << "Lift coefficient: " << same_value_index(user_flight_angle, flight_angle, lift_coefficient) << endl;

        }

        else            
        {

            interpolation(user_flight_angle, flight_angle, lift_coefficient) ;

        }

    }

    else 
    {

    cout << "You are out of range." << endl ;

    }

    while (user_input != "No") 
    {

        cout << "Do you want to enter another flight path angle?" << endl ;
        cin >> user_input ;

        if (user_input == "Yes")
        {

            cout << "What is your flight angle path?" << endl ;
            cin >> user_flight_angle ;

            if (inRange (user_flight_angle, flight_angle)) 
            {

                cout << "Lift coefficient: " << interpolation(user_flight_angle, flight_angle, lift_coefficient) << endl ;


            }

            else 
            {

            cout << "You are out of range." << endl ;

            }
        }

        if (user_input == "No")
        {

            inFS.close() ;
            exit(1) ;

        }
    }
    inFS.close() ;
}

void readData(const string &filename, vector<double> &flight_path_angle, vector<double> &lift_coefficient)
{

    ifstream inFS;
    inFS.open(filename) ;

    double num1, num2 ;

    if (!inFS.is_open())
    {

      cout << "Error opening " << filename << endl ;
      exit(1) ;

    }

    while (inFS >> num1 >> num2)
    {

      flight_path_angle.push_back(num1) ;
      lift_coefficient.push_back(num2) ;

   }
}

double interpolation(double req_angle, const vector<double> &flight_path_angle, const vector<double> &lift_coefficient)
{

    double interpol_value = 0 ;

    for (unsigned int i = 0; i < flight_path_angle.size(); i++ )
    {

        if (req_angle == flight_path_angle.at(i))
        {

            return lift_coefficient.at(i) ;

        }
        if (req_angle < flight_path_angle.at(i))
        {
            
            interpol_value = lift_coefficient.at(i - 1) + (req_angle - flight_path_angle.at(i - 1)) / (flight_path_angle.at(i) - flight_path_angle.at(i - 1)) * (lift_coefficient.at(i) - lift_coefficient.at(i - 1)) ;
    return interpol_value ;
            return interpol_value ;

        }
    }
    return interpol_value ;
}

bool isOrdered(const vector<double> &sortVector)
{
    if( sortVector.size() == 0 || sortVector.size() == 1)
    {

        return true ;

    }

    for (unsigned int i = 0; i < sortVector.size() - 1 ; i++)
    {

        if (sortVector.at(i) > sortVector.at(i + 1))
        {

            return false ;

        }   
    }

    return true ;
}

void reorder(vector<double> &flight_path_angle, vector<double> &lift_coefficient){
    
    for (unsigned int i = 0; i < flight_path_angle.size(); i++)
    {

        for (unsigned int j = i + 1; j < flight_path_angle.size() ; j++)
        {

            if (flight_path_angle.at(i) > flight_path_angle.at(j))
            {

                swap(flight_path_angle.at(i), flight_path_angle.at(j)) ;
                swap(lift_coefficient.at(i), lift_coefficient.at(j)) ;

            }
        }
    }
}

bool inRange(double user_input, const vector<double> &flight_path_angle) {

    if (user_input >= flight_path_angle.at(0) && user_input <= flight_path_angle.at(flight_path_angle.size() - 1))
    {

        return true ;

    }

    return false ;
}

int same_value_index (double user_input, const vector<double> &flight_path_angle, const vector<double> &lift_coefficient) 
{

    for (unsigned int i = 0; i < flight_path_angle.size(); i++)
    {

        if (flight_path_angle.at(i) == user_input)
        {

            return lift_coefficient.at(i) ;

        }
    }
    return 0 ;
}