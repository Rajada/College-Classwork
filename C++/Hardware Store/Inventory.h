
//  ============================================================
//
//                 Inventory base class header
//
// ============================================================
//
//
//      Copyright (C) 2014
//      Professor David E. Fox
//      Computer Science
//      American River College
//      4700 College Oak Drive
//      Sacramento, CA 95841
//
//      Permission is granted to use at your own risk and
//      distribute this software in source and binary forms
//      provided the above copyright notice and this paragraph
//      are preserved on all copies.  This software is provided
//      "as is" with no express or implied warranty.
//
//
//  ============================================================

#include <iostream>
#include "Date.h"
#include <iomanip>
#include <cstdlib>
using namespace std;



#ifndef Inventory_H_CISP_400_
#define Inventory_H_CISP_400_

class Inventory
{
  string   _UPC;
  Date     _purchased;
  float    _cost;
  string*  _suppliers;
  unsigned _num_suppliers;
public:

  Inventory();
  Inventory( string, Date, float, string* = NULL, unsigned = 0 );

  virtual ~Inventory();

  // set functions
  void set_UPC ( string );
  void set_date_purchased ( const Date& );
  void set_cost ( float );
  

  //get functions
  string get_UPC () const;
  Date get_date_purchased () const;
  float get_cost () const;

  string operator[]( unsigned ) const; // get supplier
  string& operator[] ( unsigned ); // set supplier

  virtual void display( ostream& ) const;
  virtual float selling_price ( ) const;

  virtual float gross_profit ( ) const = 0;
  virtual unsigned quantity()const = 0;

};
#endif
