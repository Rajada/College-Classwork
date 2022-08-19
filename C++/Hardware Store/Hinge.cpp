/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Hinge.h"
#include "Hardware.h"

Hinge::Hinge()
:Hardware()
{
  _hinge = Hinge::HTunknown;
  Hinge::set_material_type(Hardware::Steel);
}

Hinge::Hinge(string upc, Date purchased, float cost,
                 string* suppliers, unsigned num_suppliers)
:Hardware(upc,purchased,cost,suppliers,num_suppliers)
{
  _hinge = Hinge::HTunknown;
  Hinge::set_material_type(Hardware::Steel);
}

Hinge::Hinge(string upc, Date purchased, float cost)
:Hardware(upc, purchased, cost,Hardware::Steel,1)
{
  _hinge = Hinge::HTunknown;
}

Hinge::Hinge(string upc, Date purchased, float cost, _hinge_type ht, unsigned num_suppliers)
:Hardware(upc, purchased, cost,Hardware::Steel,1)
{
  _hinge = ht;
}

Hinge::~Hinge(){}

void Hinge::display( ostream& os) const
{
  Hardware::display(os);
  string ht[4] = {"Unknown", "Butt", "Overlay", "Offset" };
  os << "Hinge type:     " << ht[_hinge] << endl << endl;

}

float Hinge::gross_profit ( ) const
{
    return ((rand() % 12) + 2);
}
