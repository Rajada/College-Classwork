/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#ifndef HARDWOOD_H
#define HARDWOOD_H

#include "Lumber.h"

class Hardwood : public Lumber
{
public:

  enum _wood_type {WTunknown,Oak,Maple,Birch};

  Hardwood();
  Hardwood(string, Date, float);
  Hardwood(string, Date, float, string*, unsigned);
  Hardwood(string, Date, float, Hardwood::_wood_type, unsigned);

  ~Hardwood();

  void display( ostream& ) const;
  float gross_profit ( ) const;
  void set_wood_type ( Hardwood::_wood_type );
  Hardwood::_wood_type get_wood_type ( void ) const;
  void set_board_feet(unsigned);
  unsigned get_board_feet(void) const;

private:
  Hardwood::_wood_type _wood;
  unsigned _board_feet;

};
#endif
