// ============================================================
//                 Pipe Header File
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


#ifndef PIPE_H_CISP_400_
#define PIPE_H_CISP_400_

#include "Inventory.h"


class Pipe : public Inventory
{

public:

  enum Material_Type {PTunknown,Plastic,Copper,Iron};

  Pipe();
  Pipe(string, Date, float, string* = NULL, unsigned = 0);
  Pipe(string, Date, float, float, float,
       Pipe::Material_Type, unsigned );
  ~Pipe();

  void set_diameter( float );
  void set_length( float );
  void set_material_type ( Pipe::Material_Type );
  void set_in_stock ( unsigned );

  float get_diamter ( void )const;
  float get_length ( void ) const;
  Pipe::Material_Type get_material_type ( void ) const;
  unsigned get_in_stock ( void ) const;
  virtual void display( ostream& ) const;

  unsigned quantity() const;

private:
  float                _diameter;
  float                _length;
  Pipe::Material_Type  _material;
  unsigned             _in_stock;

};
#endif
