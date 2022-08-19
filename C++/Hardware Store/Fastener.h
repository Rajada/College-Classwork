/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#ifndef FASTENER_H
#define FASTENER_H

#include "Hardware.h"

class Fastener : public Hardware
{
public:

  enum _fastener_type {FTunknown,Nail,Screw,Bolt};

  Fastener();
  Fastener(string, Date, float);
  Fastener(string, Date, float, string*, unsigned);
  Fastener(string, Date, float, Fastener::_fastener_type, unsigned);

  ~Fastener();

  void display( ostream& ) const;
  float gross_profit ( ) const;
  void set_fastener_type ( Fastener::_fastener_type );
  Fastener::_fastener_type get_fastener_type ( void ) const;

private:
  Fastener::_fastener_type _fastener;

};
#endif
