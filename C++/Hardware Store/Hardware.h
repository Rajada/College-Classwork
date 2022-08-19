/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 3
    April 9, 2014

*****************************************************/


#ifndef HARDWARE_H
#define HARDWARE_H

#include "Inventory.h"


class Hardware : public Inventory
{

public:

    enum material_type {MTunknown,Stainless,Steel,Copper,Bronze};

    Hardware();
    Hardware(string, Date, float, string* = NULL, unsigned = 0);
    Hardware(string, Date, float, Hardware::material_type, unsigned );
    ~Hardware();

    void set_material_type ( Hardware::material_type );

    void set_in_stock ( unsigned );
    Hardware::material_type get_material_type ( void ) const;
    unsigned get_in_stock ( void ) const;
    virtual void display( ostream& ) const;

    unsigned quantity() const;

private:
    Hardware::material_type  _material;
    unsigned             _in_stock;
};
#endif
