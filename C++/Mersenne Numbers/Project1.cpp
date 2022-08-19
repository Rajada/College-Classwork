/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 1
    February 19, 2014

*****************************************************/

#include <iostream>
#include <time.h>
#include <sys/timeb.h>
using namespace std;

bool IsPrime( unsigned long long n );
//returns true if n is prime

unsigned long long pow2( unsigned n );
// returns 2n

unsigned long long Mersenne( unsigned n );
//returns the nth Mersenne number

unsigned long long Sqrt ( unsigned long long n );
//returns the square root of n as an integer

bool LucasLehmer ( unsigned long long n );
//returns true if the nth Mersenne number is prime. Uses the Lucas-Lehmer method

double TIME ( void )
{
   struct timeb t;
   ftime(&t);
   return ( ( (1000.0 * t.time) + t.millitm ) );
}

int main()
{
    double PTime1;
    double PTime2;
    double LTime1;
    double LTime2;

    PTime1 = TIME();

    for(int i = 3; i <= 62; i += 2)
    {
        if(IsPrime(i))
        {
            if(IsPrime(Mersenne(i)))
                cout << Mersenne(i) << " is prime." << endl;
            else
                cout << Mersenne(i) << " is not prime." << endl;
        }
    }

    PTime2 = TIME();

    LTime1 = TIME();

    for(int i = 3; i <= 62; i += 2)
    {
        if(IsPrime(i))
        {
            if(LucasLehmer(i))
                cout << Mersenne(i) << " is prime." << endl;
            else
                cout << Mersenne(i) << " is not prime." << endl;
        }
    }

    LTime2 = TIME();

    cout << endl;
    cout << "IsPrime time: " << PTime2 - PTime1 << " miliseconds" << endl;
    cout << "LucasLehmer time: " << LTime2 - LTime1 << " miliseconds" << endl;

    return 0;
}

bool IsPrime( unsigned long long n )
{
    unsigned long long Max = (Sqrt(n) + 1);

    if(n == 2)
        return true;
    else if(n == 1)
        return false;
    else
    {
        for(unsigned long long i = 2; i < Max; i++)
        {
            if(n % i == 0)
                return false;
        }
    }

    return true;
}

unsigned long long pow2( unsigned n )
{
    unsigned long long Result = 1;

    for(unsigned int i = 0; i < n; i++)
    {
        Result <<= 1;
    }

     return Result;
}

unsigned long long Mersenne( unsigned n )
{
    return(pow2(n) - 1);
}

unsigned long long Sqrt ( unsigned long long n )
{
    unsigned long long Ret = 1;

    while(Ret * Ret <= n)
        Ret++;

    return Ret;
}

bool LucasLehmer ( unsigned long long n )
{
    unsigned long long S = 4;
    const unsigned long long M = Mersenne(n);

    for(unsigned long long i = 0; i < (n - 2); i++)
    {
        S = (((S * S) - 2) % M);
    }

    if(S == 0)
        return true;
    else
        return false;
}
