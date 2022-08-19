/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#ifndef HINGE_H
#define HINGE_H

#include "Hardware.h"

class Hinge : public Hardware
{
public:

  enum _hinge_type {HTunknown,Butt,Overlay,Offset};

  Hinge();
  Hinge(string, Date, float);
  Hinge(string, Date, float, string*, unsigned);
  Hinge(string, Date, float, Hinge::_hinge_type, unsigned);

  ~Hinge();

  void display( ostream& ) const;
  float gross_profit ( ) const;
  void set_hinge_type ( Hinge::_hinge_type );
  Hinge::_hinge_type get_hinge_type ( void ) const;

private:
  Hinge::_hinge_type _hinge;

};
#endif
