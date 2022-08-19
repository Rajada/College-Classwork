/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Lumber.h"

Lumber::Lumber()
:Inventory()
{
    _surfacing = Lumber::STunknown;
}

Lumber::Lumber(string upc, Date purchased, float cost,
           string* sp, unsigned ns)
:Inventory(upc, purchased, cost, sp, ns)
{
  _surfacing = Lumber::STunknown;
}

Lumber::Lumber(string upc, Date purchased, float cost,
           Lumber::surfacing_type st, unsigned ins )
:Inventory(upc, purchased, cost)
{
  _surfacing = st;
  _in_stock = ins;
  assert ( st <= S4S );
}
Lumber::~Lumber()
{
}

void Lumber::set_surfacing_type (Lumber::surfacing_type st)
{
  _surfacing = st;
  assert(st <= S4S);
}
void Lumber::set_in_stock ( unsigned ins )
{
  _in_stock = ins;
}

Lumber::surfacing_type Lumber::get_surfacing_type ( ) const
{
  return _surfacing;
}

unsigned Lumber::get_in_stock ( ) const
{
  return _in_stock;
}

void Lumber::display( ostream& os ) const
{
  Inventory::display(os);
     string st[4] = {"Unknown", "Rough", "S2S","S4S" };
  os << "Surfacing:         " << st[_surfacing] << endl;
}

unsigned Lumber::quantity ( ) const
{
  return _in_stock;
}
