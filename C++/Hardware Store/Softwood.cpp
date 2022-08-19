/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Softwood.h"
#include "Lumber.h"

Softwood::Softwood()
:Lumber()
{
  Softwood::set_thickness(1);
  Softwood::set_surfacing_type(Lumber::S4S);
}

Softwood::Softwood(string upc, Date purchased, float cost,
                 string* suppliers, unsigned num_suppliers)
:Lumber(upc,purchased,cost,suppliers,num_suppliers)
{
  Softwood::set_thickness(1);
  Softwood::set_surfacing_type(Lumber::S4S);
}

Softwood::Softwood(string upc, Date purchased, float cost)
:Lumber(upc, purchased, cost,Lumber::S4S,1)
{
  Softwood::set_thickness(1);
}

Softwood::Softwood(string upc, Date purchased, float cost, unsigned thick, unsigned num_suppliers)
:Lumber(upc, purchased, cost,Lumber::S4S,1)
{
  Softwood::set_thickness(thick);
}

Softwood::~Softwood(){}

void Softwood::display( ostream& os) const
{
  Lumber::display(os);
  os << "Softwood thickness:     " << Softwood::get_thickness() << endl << endl;

}

float Softwood::gross_profit ( ) const
{
    return ((rand() % 12) + 2);
}

  void Softwood::set_thickness ( unsigned t)
  {
      _thickness = t;
  }
  unsigned Softwood::get_thickness ( void ) const
  {
      return _thickness;
  }
