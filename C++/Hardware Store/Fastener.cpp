/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Fastener.h"
#include "Hardware.h"

Fastener::Fastener()
:Hardware()
{
  _fastener = Fastener::FTunknown;
  Fastener::set_material_type(Hardware::Steel);
}

Fastener::Fastener(string upc, Date purchased, float cost,
                 string* suppliers, unsigned num_suppliers)
:Hardware(upc,purchased,cost,suppliers,num_suppliers)
{
  _fastener = Fastener::FTunknown;
  Fastener::set_material_type(Hardware::Steel);
}

Fastener::Fastener(string upc, Date purchased, float cost)
:Hardware(upc, purchased, cost,Hardware::Steel,1)
{
  _fastener = Fastener::FTunknown;
}

Fastener::Fastener(string upc, Date purchased, float cost, _fastener_type ft, unsigned num_suppliers)
:Hardware(upc, purchased, cost,Hardware::Steel,1)
{
  _fastener = ft;
}

Fastener::~Fastener(){}

void Fastener::display( ostream& os) const
{
  Hardware::display(os);
  string ft[4] = {"Unknown", "Nail", "Screw", "Bolt" };
  os << "Fastener type:     " << ft[_fastener] << endl << endl;

}

float Fastener::gross_profit ( ) const
{
    return ((rand() % 12) + 2);
}
