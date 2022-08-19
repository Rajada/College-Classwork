/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 2
    March 3, 2014

*****************************************************/

#include "Rational.h"

int main()
{
  cout << endl << endl;
  Rational r1 = Rational(1,3);
  r1.Display();
  cout <<" + ";
  Rational r2 = Rational(2,-3);
  r2.Display();
  r1.Add(r2);
  cout << " = ";
  r1.Display();
  cout << endl;
  r1.Display();
  cout <<" - ";
  r2.Display();
  r1.Subtract(r2);
  cout << " = ";
  r1.Display();
  cout << endl;
  r1.Display();
  cout <<" * ";
  Rational r3 = Rational(1,4);
  r3.Display();
  r1.Multiply(r3);
  cout << " = ";
  r1.Display();
  cout << endl;
  r1.Display();
  cout <<" / ";
  r3.Display();
  r1.Divide(r3);
  cout << " = ";
  r1.Display();
  cout << endl;
  r1.Display();
  cout <<" + ";
  Rational r4 = Rational(0,7);
  r4.Display();
  r1.Add(r4);
  cout << " = ";
  r1.Display();
  cout << endl;
  r1.Display();
  cout <<" + ";
  Rational r5 = Rational(0,0);
  r4.Display();
  r1.Add(r5);
  cout << " = ";
  r1.Display();
  cout << endl;
}
