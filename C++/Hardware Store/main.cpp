/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 4 & 5
    March 19, 2014

*****************************************************/

#include "Store.h"

using namespace std;

int main()
{
    Store* MyStore = new Store();
    MyStore->Run();
    delete MyStore;

    return 0;
}
