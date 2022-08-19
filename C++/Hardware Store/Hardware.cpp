/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Hardware.h"

Hardware::Hardware()
:Inventory()
{
    _material = Hardware::MTunknown;
}

Hardware::Hardware(string upc, Date purchased, float cost,
           string* sp, unsigned ns)
:Inventory(upc, purchased, cost, sp, ns)
{
  _material = Hardware::MTunknown;
}

Hardware::Hardware(string upc, Date purchased, float cost,
           Hardware::material_type mt, unsigned ins )
:Inventory(upc, purchased, cost)
{
  _material = mt;
  _in_stock = ins;
  assert ( mt <= Steel );
}
Hardware::~Hardware()
{
}

void Hardware::set_material_type (Hardware::material_type mt)
{
  _material = mt;
  assert(mt <= Steel);
}
void Hardware::set_in_stock ( unsigned ins )
{
  _in_stock = ins;
}

Hardware::material_type Hardware::get_material_type ( ) const
{
  return _material;
}

unsigned Hardware::get_in_stock ( ) const
{
  return _in_stock;
}

void Hardware::display( ostream& os ) const
{
  Inventory::display(os);
     string mt[5] = {"Unknown", "Stainless", "Steel", "Copper", "Bronze" };
  os << "Material:         " << mt[_material] << endl;
}

unsigned Hardware::quantity ( ) const
{
  return _in_stock;
}
