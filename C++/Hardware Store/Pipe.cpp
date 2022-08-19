// ============================================================
//                 Pipe implementation File
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

#include "Pipe.h"

Pipe::Pipe()
:Inventory()
{
  _diameter = 0;
  _length = 0;
  _material = Pipe::PTunknown;
}

Pipe::Pipe(string upc, Date purchased, float cost,
           string* sp, unsigned ns)
:Inventory(upc, purchased, cost, sp, ns)
{
  _diameter = 0;
  _length = 0;
  _material = Pipe::PTunknown;
}

Pipe::Pipe(string upc, Date purchased, float cost,
           float dia, float len, Pipe::Material_Type pmt, unsigned ins )
:Inventory(upc, purchased, cost)
{
  _diameter = dia;
  _length = len;
  _material = pmt;
  _in_stock = ins;
  assert ( _diameter >= 0.0 );
  assert ( _length >= 0.0 );
  assert ( pmt <= Iron );
}
Pipe::~Pipe()
{
}

void Pipe::set_diameter( float dia )
{
  _diameter = dia;
  assert ( _diameter >= 0.0 );
}

void Pipe::set_length( float len )
{
  _length = len;
   assert ( _length >= 0.0 );
}
void Pipe::set_material_type (Pipe::Material_Type pmt)
{
  _material = pmt;
  assert(pmt <= Iron);
}
void Pipe::set_in_stock ( unsigned ins )
{
  _in_stock = ins;
}

float Pipe::get_diamter ( void )const
{
  return _diameter;
}
float Pipe::get_length ( void ) const
{
  return _length;
}

Pipe::Material_Type Pipe::get_material_type ( ) const
{
  return _material;
} 

unsigned Pipe::get_in_stock ( ) const
{
  return _in_stock;
}

void Pipe::display( ostream& os ) const
{
  Inventory::display(os);
  os << "Diameter:         " << _diameter<<"\"" << endl
     << "Length:           " << _length<<"'"<<endl;
     string pmt[4] = {"Unknown", "Plastic", "Copper","Iron" };
  os << "Material:         " << pmt[_material] << endl;
}

unsigned Pipe::quantity ( ) const
{
  return _in_stock * _length;
}
