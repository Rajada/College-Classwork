/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 3
    March 19, 2014

*****************************************************/
#include <iostream>
#include <stdlib.h>

#ifndef RATIONAL_H
#define RATIONAL_H

using namespace std;

class Rational
{
    long long _P;
    long long _Q;
    void _Reduce();

public:

    Rational();
    Rational(long long P, long long Q = 1);
    Rational(const Rational&);

    Rational& operator= (const Rational&);
    Rational& operator+= (const Rational&);
    Rational& operator-= (const Rational&);
    Rational& operator*= (const Rational&);
    Rational& operator/= (const Rational&);
    friend ostream& operator<< (ostream&, const Rational&);
    friend istream& operator>> (istream&, Rational&);
    Rational operator+ (const Rational&) const;
    Rational operator+ (long long) const;
    friend Rational operator+ (long long, const Rational&);
    Rational operator- (const Rational&) const;
    Rational operator- (long long) const;
    friend Rational operator- (long long, const Rational&);
    Rational operator* (const Rational&) const;
    Rational operator* (long long) const;
    friend Rational operator* (long long, const Rational&);
    Rational operator/ (const Rational&) const;
    Rational operator/ (long long) const;
    friend Rational operator/ (long long, const Rational&);
    bool operator== (const Rational&) const; //implement this one
    bool operator== (long long) const;
    friend bool operator== (long long, const Rational&);
    bool operator!= (const Rational&) const;
    bool operator!= (long long) const;
    friend bool operator!= (long long, const Rational&);
    bool operator> (const Rational&) const; // implement this one
    bool operator> (long long) const;
    friend bool operator> (long long, const Rational&);
    bool operator< (const Rational&) const;
    bool operator< (long long) const;
    friend bool operator< (long long, const Rational&);
    bool operator>= (const Rational&) const;
    bool operator>= (long long) const;
    friend bool operator>= (long long, const Rational&);
    bool operator<= (const Rational&) const;
    bool operator<= (long long) const;
    friend bool operator<= (long long, const Rational&);
    Rational operator++ (int); //post
    Rational operator-- (int); //post
    Rational& operator++ (); //pre
    Rational& operator-- (); //pre
    Rational operator- () const;
    Rational operator+ () const;
    Rational pow( unsigned exp ) const; //returns (*this)exp
    Rational inverse() const;
};
#endif // RATIONAL_H
