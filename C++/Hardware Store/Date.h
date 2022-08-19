// ============================================================
//                 Date Header File
// ============================================================
//
//      Copyright (C) 2012
//      Professor David E. Fox
//      Computer Science
//      American River College
//      4700 College Oak Drive
//      Sacramento, CA  95841
//
//      Permission is granted to use at your own risk and
//      distribute this software in source and binary forms
//      provided the above copyright notice and this paragraph
//      are preserved on all copies.  This software is provided
//      "as is" with no express or implied warranty.
//
// ============================================================

#ifndef DATE_H_DEF_
#define DATE_H_DEF_
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

enum DATE_CHANGE {MONTH, DAY, YEAR};
enum DATE_STYLE {MM_DD_YYYY, MON_DD_YYYY, DD_MM_YYYY, D_ROM_YYYY};


class Date
{
  unsigned date;
  DATE_STYLE ds;
  unsigned days_in_month()const;
  void set_date(unsigned m, unsigned d, unsigned y );
  void set_day(unsigned);
  void set_month(unsigned);
  void set_year(unsigned);

public:
  Date();
  Date ( unsigned m, unsigned d, unsigned y );
  Date ( const Date& );
  Date& operator= ( const Date& );
  Date& operator+= ( DATE_CHANGE );
  Date& operator-= ( DATE_CHANGE );
  Date operator+ ( DATE_CHANGE ) const;
  Date operator- ( DATE_CHANGE ) const;
  int operator- ( const Date& ) const;

  Date operator++ (int);
  Date& operator++ ( );
  Date operator-- (int);
  Date& operator-- ( );

  bool is_leap_year() const;


  inline void set_date_style( DATE_STYLE DS ) { ds = DS;}

  friend ostream& operator<< ( ostream&, const Date& );
  friend istream& operator>> ( istream&, Date& );

  unsigned month()const;
  unsigned day()const;
  unsigned year()const;
  bool IsPalindrome()const;
  bool operator== ( const Date& )const;
  bool operator!= ( const Date& ) const;
  bool operator> ( const Date& ) const;
  bool operator< ( const Date& ) const;
  bool operator>= ( const Date& ) const;
  bool operator<= ( const Date& ) const;

  bool weekday ( ) const; //returns true if the day is Monday - Friday



};



#endif
