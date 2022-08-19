// ============================================================
//                 Plastic Pipe Header File
// ============================================================
//
//      Copyright (C) 2014
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

#ifndef PLASTIC_H_CISP_400_
#define PLASTIC_H_CISP_400_

#include "Pipe.h"


class Plastic : public Pipe
{
public:

  enum Material_Type {Unknown,ABS,PVC,CPVC};

  Plastic();
  Plastic(string, Date, float);
  Plastic(string, Date, float, string*, unsigned);
  Plastic(string, Date, float, float, float);
  Plastic(string, Date, float, float, float,
          Plastic::Material_Type,float);

  ~Plastic();

  void display( ostream& ) const;
  float gross_profit ( ) const;

private:
  Plastic::Material_Type _material;
  float                  _wall_thickness;


};
#endif
