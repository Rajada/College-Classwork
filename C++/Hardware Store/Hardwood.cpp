/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Hardwood.h"
#include "Lumber.h"

Hardwood::Hardwood()
:Lumber()
{
  _wood = Hardwood::WTunknown;
  Hardwood::set_surfacing_type(Lumber::S4S);
}

Hardwood::Hardwood(string upc, Date purchased, float cost,
                 string* suppliers, unsigned num_suppliers)
:Lumber(upc,purchased,cost,suppliers,num_suppliers)
{
  _wood = Hardwood::WTunknown;
  Hardwood::set_surfacing_type(Lumber::S4S);
}

Hardwood::Hardwood(string upc, Date purchased, float cost)
:Lumber(upc, purchased, cost,Lumber::S4S,1)
{
  _wood = Hardwood::WTunknown;
}

Hardwood::Hardwood(string upc, Date purchased, float cost, _wood_type wt, unsigned num_suppliers)
:Lumber(upc, purchased, cost,Lumber::S4S,1)
{
  _wood = wt;
}

Hardwood::~Hardwood(){}

void Hardwood::display( ostream& os) const
{
  Lumber::display(os);
  string wt[4] = {"Unknown", "Oak", "Maple", "Birch" };
  os << "Hardwood type:     " << wt[_wood] << endl << endl;

}

float Hardwood::gross_profit ( ) const
{
    return ((rand() % 12) + 2);
}
