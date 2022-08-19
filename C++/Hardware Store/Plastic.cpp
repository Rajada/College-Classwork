// ============================================================
//                 Plastic Pipe Implementation File
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

#include "Plastic.h"
#include "Pipe.h"

Plastic::Plastic()
:Pipe()
{
  _material = Plastic::Unknown;
  _wall_thickness = 0.0;
  Pipe::set_material_type(Pipe::Plastic);
}

Plastic::Plastic(string upc, Date purchased, float cost, 
                 string* suppliers, unsigned num_suppliers)
:Pipe(upc,purchased,cost,suppliers,num_suppliers)
{
  _material = Plastic::Unknown;
  _wall_thickness = 0.0;
  Pipe::set_material_type(Pipe::Plastic);
}

Plastic::Plastic(string upc, Date purchased, float cost)
:Pipe(upc, purchased, cost,0.0,0.0,Pipe::Plastic,1)
{
  _material = Plastic::Unknown;
  _wall_thickness = 0.0;
}

Plastic::Plastic(string upc, Date purchased, float cost,
                 float dia, float len)
:Pipe(upc, purchased, cost,dia,len,Pipe::Plastic,1)
{
  _material = Plastic::Unknown;
  _wall_thickness = 0.0;
}

Plastic::Plastic(string upc, Date purchased, float cost,
        float dia, float len, Material_Type pmt ,float wt)
:Pipe(upc, purchased, cost,dia,len,Pipe::Plastic,1)
{
  _material = pmt;
  _wall_thickness = wt;
}

Plastic::~Plastic(){}

void Plastic::display( ostream& os) const
{
  Pipe::display(os);
  string pt[4] = {"Unknown", "ABS", "PVC", "CPVC" };
  os << "Plastic type:     " << pt[_material]<<endl
     << "Wall Thickness:   " << _wall_thickness <<"\""<< endl;;

}

float Plastic::gross_profit ( ) const
{

  float  price_per_ft[4] = { 0.0, .5, .75, 1 };
  return get_length() * price_per_ft[_material] - get_length()*get_cost();;
}
