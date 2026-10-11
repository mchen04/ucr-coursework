#include <iostream>

using namespace std;

// Rational Class declaration
class Rational {
   private:
      int numerator;
      int denominator; 
   public:
      Rational();
      explicit Rational(int); 
      Rational(int, int); 
      Rational add(const Rational &) const; 
      Rational subtract(const Rational &) const; 
      Rational multiply(const Rational &) const; 
      Rational divide(const Rational &) const;
      void simplify();
      void display() const;
   private:
      int gcd(int, int) const;
};

// Implement Rational class member functions here

Rational::Rational (int n, int d) {
   numerator = n ;
   denominator = d ;
}

Rational::Rational (int n) {
   denominator = 1 ;
   numerator = n ;
}

Rational::Rational () {
   numerator = 0 ;
   denominator = 1 ;
}


Rational Rational::add(const Rational &x) const{
   Rational result ;
   
   result.numerator = ( numerator * x.denominator ) + ( denominator * x.numerator ) ;
   result.denominator =  ( denominator * x.denominator ) ;
   
   return result ;
}

Rational Rational::subtract(const Rational &x) const{
   Rational result ;
   
   result.numerator = ( numerator * x.denominator ) - ( denominator * x.numerator ) ;
   result.denominator =  ( denominator * x.denominator ) ;
   
   return result ;
}

Rational Rational::multiply(const Rational &x) const{
   Rational result ;
   
   result.numerator = ( numerator * x.numerator ) ;
   result.denominator =  ( denominator * x.denominator ) ;
   
   return result ;
}

Rational Rational::divide(const Rational &x) const{
   Rational result ;
   
   result.numerator = ( numerator * x.denominator ) ;
   result.denominator =  ( denominator * x.numerator ) ;
   
   return result ;
}

void Rational::display() const{
   
   cout << numerator << " / " << denominator ;

}

void Rational::simplify() {
   
   int gcd_div = gcd(numerator, denominator) ;

   numerator /= gcd_div ;
   denominator /= gcd_div ;

}

int Rational::gcd(int num, int denom) const {
   int small ;

   if ( num <= denom ) {
      small = num ;
   } 
   else {
      small = denom ;
   }

   for (int i = small; i >= 2; i--) {
      if ( ( num % i == 0 ) && ( denom % i == 0 ) ){
         return i ;
      }
   }
   return 1;
}

// Do not change any of the code below this line!!

Rational getRational();
void displayResult(const string &, const Rational &, const Rational&, const Rational&);

int main() {
   Rational A, B, result;
   char choice;
   
   cout << "Enter Rational A:" << endl;
   A = getRational();
   cout << endl;
   
   cout << "Enter Rational B:" << endl;
   B = getRational();
   cout << endl;
   
   cout << "Enter Operation:" << endl
      << "a - Addition (A + B)" << endl
      << "s - Subtraction (A - B)" << endl
      << "m - Multiplication (A * B)" << endl
      << "d - Division (A / B)" << endl
      << "y - Simplify A" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 'a') {
      result = A.add(B);
      displayResult("+", A, B, result);
   } else if (choice == 's') {
      result = A.subtract(B);
      displayResult("-", A, B, result);
   } else if (choice == 'm') {
      result = A.multiply(B);
      displayResult("*", A, B, result);
   } else if (choice == 'd') {
      result = A.divide(B);
      displayResult("/", A, B, result);
   } else if (choice == 'y') {
      A.simplify();
      A.display();
   } else {
      cout << "Unknown Operation";
   }
   cout << endl;
   
   return 0;
}


Rational getRational() {
   int choice;
   int numer, denom;
   
   cout << "Which Rational constructor? (Enter 2, 1, or 0)" << endl
      << "2 - 2 parameters (numerator & denominator)" << endl
      << "1 - 1 parameter (numerator)" << endl
      << "0 - 0 parameters (default)" << endl;
   cin >> choice;
   cout << endl;
   
   if (choice == 2) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      cout << "denominator? ";
      cin >> denom;
      cout << endl;
      return Rational(numer, denom);
   } else if (choice == 1) {
      cout << "numerator? ";
      cin >> numer;
      cout << endl;
      return Rational(numer);
   } else {
      return Rational();
   }
}

void displayResult(const string &op, const Rational &lhs, const Rational&rhs, const Rational &result) {
   cout << "(";
   lhs.display();
   cout << ") " << op << " (";
   rhs.display();
   cout << ") = (";
   result.display();
   cout << ")";
}

