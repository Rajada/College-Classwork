/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 3
    April 9, 2014

*****************************************************/

#include "Inventory.h"
#include "Pipe.h"
#include "Plastic.h"
#include "Hardware.h"
#include "Fastener.h"
#include "Hinge.h"
#include "Lumber.h"
#include "Hardwood.h"
#include "Softwood.h"
#include <iostream>

using namespace std;

#ifndef STORE_H
#define STORE_H

const unsigned MAX_ITEMS = 50;

class Store
{
public:

    Store();
    ~Store();
    void Run();


private:

    Inventory* _inv[MAX_ITEMS];
    unsigned _num_items;

    void _case1();
    void _case2();
    void _case3();
    void _case4();
};
#endif
