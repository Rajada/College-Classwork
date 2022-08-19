/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 3
    March 19, 2014

*****************************************************/

#include "Rational.h"
using namespace std;

Rational::Rational()
{
    _P = 0;
    _Q = 1;
}

Rational::Rational(long long P, long long Q)
{
    _P = P;
    _Q = Q;
    _Reduce();
}

Rational::Rational(const Rational& R)
{
    _P = R._P;
    _Q = R._Q;
}

void Rational::_Reduce()
{
    long long PTemp = _P;
    long long QTemp = _Q;
    long long Least = 0;

    if(_Q == 0)
    {
        cout << "Cannot divide by 0!" << endl;
        cin.get();
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



Rational& Rational::operator= (const Rational& R)
{
    _P = R._P;
    _Q = R._Q;

    return *this;
}

Rational& Rational::operator+= (const Rational& R)
{
    _P = (_P * R._Q) + (R._P * _Q);
    _Q *= R._Q;
    _Reduce();

    return *this;
}

Rational& Rational::operator-= (const Rational& R)
{
    operator+= (-R);

    return *this;
}

Rational& Rational::operator*= (const Rational& R)
{
    _P *= R._P;
    _Q *= R._Q;
    _Reduce();

    return *this;
}

Rational& Rational::operator/= (const Rational& R)
{
    if(R._P == 0)
    {
        cout << "Cannot divide by 0!" << endl;
        cin.get();
        exit(1);
    }

    operator*= (R.inverse());

    return *this;
}

ostream& operator<< (ostream& os, const Rational& R)
{
    os << R._P << ':' << R._Q;

    return os;
}

istream& operator>> (istream& is, Rational& R)
{
    char c;

    is >> R._P;
    is >> c;
    is >> R._Q;

    return is;
}

Rational Rational::operator+ (const Rational& R) const
{
    return Rational(*this) += R;
}

Rational Rational::operator+ (long long L) const
{
    return (*this + Rational(L));
}

Rational operator+ (long long L, const Rational& R)
{
    return (Rational(L) + R);
}

Rational Rational::operator- (const Rational& R) const
{
    return Rational(*this) -= R;
}
Rational Rational::operator- (long long L) const
{
    return (*this - Rational(L));
}
Rational operator- (long long L, const Rational& R)
{
    return (Rational(L) - R);
}
Rational Rational::operator* (const Rational& R) const
{
    return Rational(*this) *= R;
}
Rational Rational::operator* (long long L) const
{
    return (*this * Rational(L));
}
Rational operator* (long long L, const Rational& R)
{
    return (Rational(L) * R);
}
Rational Rational::operator/ (const Rational& R) const
{
    return Rational(*this) /= R;
}
Rational Rational::operator/ (long long L) const
{
     return (*this / Rational(L));
}

Rational operator/ (long long L, const Rational& R)
{
    return (Rational(L) / R);
}

bool Rational::operator== (const Rational& R) const
{
    return((_P == R._P) && (_Q == R._Q));
}

bool Rational::operator== (long long L) const
{
    return(*this == Rational(L));
}
bool operator== (long long L, const Rational& R)
{
    return(Rational(L) == R);
}

bool Rational::operator!= (const Rational& R) const
{
    return !(*this == R);
}

bool Rational::operator!= (long long L) const
{
    return !(*this == Rational(L));
}

bool operator!= (long long L, const Rational& R)
{
    return !(Rational(L) == R);
}

bool Rational::operator> (const Rational& R) const
{
    return((_P * R._Q) > (R._P * _Q));
}

bool Rational::operator> (long long L) const
{
    return(*this > Rational(L));
}

bool operator> (long long L, const Rational& R)
{
    return(Rational(L) > R);
}

bool Rational::operator< (const Rational& R) const
{
    return !(*this >= R);
}

bool Rational::operator< (long long L) const
{
    return(*this < Rational(L));
}

bool operator< (long long L, const Rational& R)
{
    return(Rational(L) < R);
}

bool Rational::operator>= (const Rational& R) const
{
    return((*this == R) || (*this > R));
}

bool Rational::operator>= (long long L) const
{
    return(*this >= Rational(L));
}

bool operator>= (long long L, const Rational& R)
{
    return(Rational(L) >= R);
}

bool Rational::operator<= (const Rational& R) const
{
    return((*this == R) || (*this < R));
}

bool Rational::operator<= (long long L) const
{
    return(*this <= Rational(L));
}

bool operator<= (long long L, const Rational& R)
{
    return(Rational(L) <= R);
}

Rational Rational::operator++ (int i) //post
{
    Rational ret(*this);

    _P += _Q;
    return ret;
}

Rational Rational::operator-- (int i) //post
{
    Rational ret(*this);

    _P -= _Q;
    return ret;
}

Rational& Rational::operator++ () //pre
{
    _P += _Q;
    return *this;
}

Rational& Rational::operator-- () //pre
{
    _P -= _Q;
    return *this;
}

Rational Rational::operator- () const
{
    return Rational(-_P,_Q);
}

Rational Rational::operator+ () const
{
    return *this;
}

Rational Rational::pow( unsigned exp) const
{
    if(exp == 0)
        return Rational(1,1);

    return ((*this) * pow(exp - 1));
}

Rational Rational::inverse() const
{
    if(_P == 0)
    {
        cout << "Cannot divide by 0!" << endl;
        cin.get();
        exit(1);
    }

    return Rational(_Q, _P);
}
