/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 2
    March 3, 2014

*****************************************************/

#include "Rational.h"

Rational::Rational()
{
    _P = 0;
    _Q = 1;
}

Rational::Rational(int P, int Q)
{
    _P = P;
    _Q = Q;
    Reduce();
}

void Rational::Display() const
{
    if(_P == _Q)
        cout << _P;
    else
        cout << _P << ":" << _Q;
}

void Rational::Add(const Rational& R)
{
    _P = ((_P * R._Q) + (_Q * R._P));
    _Q = _Q * R._Q;
    Reduce();
}

void Rational::Subtract(const Rational& R)
{
    _P = ((_P * R._Q) - (_Q * R._P));
    _Q = _Q * R._Q;
    Reduce();
}

void Rational::Multiply(const Rational& R)
{
    _P *= R._P;
    _Q *= R._Q;
    Reduce();
}

void Rational::Divide(const Rational& R)
{
    _P *= R._Q;
    _Q *= R._P;
    Reduce();
}

void Rational::Reduce()
{
    int PTemp = _P;
    int QTemp = _Q;
    int Least = 0;

    if(_Q == 0)
    {
        cout << "Cannot divide by zero." << endl;
        exit(1);
    }

    if(_Q < 0)
    {
        _P *= -1;
        _Q *= -1;
    }

    if(PTemp < 0)
        PTemp *= -1;
    if(QTemp < 0)
        QTemp *= -1;

    if(PTemp < QTemp)
        Least = PTemp;
    else
        Least = QTemp;

    for(int i = Least; i > 0; i--)
    {
        if((_P % i == 0) && (_Q % i == 0))
        {
            _P /= i;
            _Q /= i;
            i = 0;
        }
    }
}
