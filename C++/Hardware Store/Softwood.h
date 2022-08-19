/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#ifndef SOFTWOOD_H
#define SOFTWOOD_H

#include "Lumber.h"

class Softwood : public Lumber
{
public:

  Softwood();
  Softwood(string, Date, float);
  Softwood(string, Date, float, string*, unsigned);
  Softwood(string, Date, float, unsigned, unsigned);

  ~Softwood();

  void display( ostream& ) const;
  float gross_profit ( ) const;
  void set_thickness ( unsigned );
  unsigned get_thickness ( void ) const;

private:
  unsigned _thickness;

};
#endif
