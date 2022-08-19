/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 3
    April 9, 2014

*****************************************************/


#ifndef LUMBER_H
#define LUMBER_H

#include "Inventory.h"


class Lumber : public Inventory
{

public:

    enum surfacing_type {STunknown,Rough,S2S,S4S};

    Lumber();
    Lumber(string, Date, float, string* = NULL, unsigned = 0);
    Lumber(string, Date, float, Lumber::surfacing_type, unsigned );
    ~Lumber();

    void set_surfacing_type ( Lumber::surfacing_type );

    void set_in_stock ( unsigned );
    Lumber::surfacing_type get_surfacing_type ( void ) const;
    unsigned get_in_stock ( void ) const;
    virtual void display( ostream& ) const;

    unsigned quantity() const;

private:
    Lumber::surfacing_type  _surfacing;
    unsigned             _in_stock;
};
#endif
