/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Store.h"

const unsigned EXIT_CODE = 'E';

Store::Store()
{
    for(unsigned i = 0; i < MAX_ITEMS; i++)
    {
        _inv[i] = NULL;
    }

    _num_items = 0;
}

Store::~Store()
{
     for(unsigned i = 0; i < MAX_ITEMS; i++)
    {
        delete _inv[i];
    }
}

unsigned char Menu()
{
    unsigned char c;

    cout << endl << "A: Put a new item into the store" << endl
    << "B: Display selling prices" << endl
    << "C: Display gross profit margins" << endl
    << "D: Display all items" << endl
    << "E: Exit" << endl;
    cout << "Enter your choice: ";

    cin >> c;
    c &= 223;

    return c;
}

void Store::_case1()
{
    if(_num_items <= 49)
    {
        if(rand() %5 == 0)
        {
            _inv[_num_items++] = new Plastic();
        }
        else if(rand() %5 == 1)
        {
            _inv[_num_items++] = new Hardwood();
        }
        else if(rand() %5 == 2)
        {
            _inv[_num_items++] = new Softwood();
        }
        else if(rand() %5 == 3)
        {
            _inv[_num_items++] = new Fastener();
        }
        else
        {
            _inv[_num_items++] = new Hinge();
        }

        _inv[_num_items - 1] -> set_cost(rand() %100);
    }
    else
        cout << "Store is full!" << endl << endl;
}

void Store::_case2()
{
    for(unsigned i = 0; i < _num_items; i++)
    {
        cout << endl << _inv[i] -> selling_price() << endl;
    }

    cout << endl;
}

void Store::_case3()
{
    for(unsigned i = 0; i < _num_items; i++)
    {
        cout << endl << _inv[i] -> gross_profit() << endl;
    }

    cout << endl;
}

void Store::_case4()
{
    for(unsigned i = 0; i < _num_items; i++)
    {
        cout << endl;
        _inv[i] -> display(cout);
    }
}

void Store::Run()
{
    unsigned char Choice;

    Choice = Menu();

    while(Choice != EXIT_CODE)
    {
        switch(Choice)
        {
            case 'A': _case1();
                break;
            case 'B': _case2();
                break;
            case 'C': _case3();
                break;
            case 'D': _case4();
                break;
            default:
                cout << endl << "You entered an invalid choice: " << Choice;
                break;
        }

        Choice = Menu();
    }

    cout << "Goodbye!" << endl;
}

