/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 2
    March 3, 2014

*****************************************************/
#include <iostream>
#include <stdlib.h>

#ifndef RATIONAL_H
#define RATIONAL_H

using namespace std;

class Rational
{
    int _P;
    int _Q;
    void Reduce();

public:

    Rational();
    Rational(int P, int Q = 1);
    void Display() const; // _P:_Q
    void Add(const Rational&);
    void Subtract(const Rational&);
    void Multiply(const Rational&);
    void Divide(const Rational&);
};
#endif // RATIONAL_H
