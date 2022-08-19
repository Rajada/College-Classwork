/*****************************************************

    Jared Petersen
    CISP 400 - MW 3:00 pm
    Programming Project 3
    March 19, 2014

*****************************************************/

#include "Rational.h"
using namespace std;

int main()
{
    Rational R0(1,1);
    Rational R1(1,1);
    long long L1 = 2;

    while(true)
    {
        cout << "ENTER R0: ";
        cin >> R0;
        cout << "ENTER R1: ";
        cin >> R1;

        cout << endl;
        cout << R0 << "+" << R1 << "=" << (R0 + R1);
        cout << endl;
        cout << R0 << "-" << R1 << "=" << (R0 - R1);
        cout << endl;
        cout << R0 << "*" << R1 << "=" << (R0 * R1);
        cout << endl;
        cout << R0 << "/" << R1 << "=" << (R0 / R1);
        cout << endl;
        cout << L1 << "+" << R1 << "=" << (L1 + R1);
        cout << endl;
        cout << L1 << "-" << R1 << "=" << (L1 - R1);
        cout << endl;
        cout << L1 << "*" << R1 << "=" << (L1 * R1);
        cout << endl;
        cout << L1 << "/" << R1 << "=" << (L1 / R1);
        cout << endl;
        cout << R0 << "+" << L1 << "=" << (R0 + L1);
        cout << endl;
        cout << R0 << "-" << L1 << "=" << (R0 - L1);
        cout << endl;
        cout << R0 << "*" << L1 << "=" << (R0 * L1);
        cout << endl;
        cout << R0 << "/" << L1 << "=" << (R0 / L1);
        cout << endl << endl;

        cout << R0 << "+=" << R1 << "=";
        R0 += R1;
        cout << R0;
        cout << endl;
        cout << R0 << "-=" << R1 << "=";
        R0 -= R1;
        cout << R0;
        cout << endl;
        cout << R0 << "*=" << R1 << "=";
        R0 *= R1;
        cout << R0;
        cout << endl;
        cout << R0 << "/=" << R1 << "=";
        R0 /= R1;
        cout << R0;
        cout << endl;
        cout << R0 << "+=" << L1 << "=";
        R0 += L1;
        cout << R0;
        cout << endl;
        cout << R0 << "-=" << L1 << "=";
        R0 -= L1;
        cout << R0;
        cout << endl;
        cout << R0 << "*=" << L1 << "=";
        R0 *= L1;
        cout << R0;
        cout << endl;
        cout << R0 << "/=" << L1 << "=";
        R0 /= L1;
        cout << R0;
        cout << endl << endl;

        cout << R0 << "==" << R1 << ": " << (R0 == R1);
        cout << endl;
        cout << R0 << "==" << R0 << ": " << (R0 == R0);
        cout << endl;
        cout << R0 << "!=" << R1 << ": " << (R0 != R1);
        cout << endl;
        cout << R0 << "!=" << R1 << ": " << (R0 != R0);
        cout << endl;
        cout << L1 << "==" << R1 << ": " << (L1 == R1);
        cout << endl;
        cout << L1 << "==" << R0 << ": " << (L1 == R0);
        cout << endl;
        cout << L1 << "!=" << R1 << ": " << (L1 != R1);
        cout << endl;
        cout << L1 << "!=" << R1 << ": " << (L1 != R0);
        cout << endl;
        cout << R0 << "==" << L1 << ": " << (R0 == L1);
        cout << endl;
        cout << R0 << "==" << L1 << ": " << (R0 == L1);
        cout << endl;
        cout << R0 << "!=" << L1 << ": " << (R0 != L1);
        cout << endl;
        cout << R0 << "!=" << L1 << ": " << (R0 != L1);
        cout << endl << endl;

        cout << R0 << ">=" << R1 << ": " << (R0 >= R1);
        cout << endl;
        cout << R0 << ">=" << R0 << ": " << (R0 >= R0);
        cout << endl;
        cout << R0 << ">" << R1 << ": " << (R0 > R1);
        cout << endl;
        cout << R0 << ">" << R0 << ": " << (R0 > R0);
        cout << endl;
        cout << L1 << ">=" << R1 << ": " << (L1 >= R1);
        cout << endl;
        cout << L1 << ">" << R0 << ": " << (L1 > R0);
        cout << endl << endl;

        cout << R0 << " =" << (R0++)  << "++";
        cout << endl;
        cout << R0 << " =" << (R0--)  << "--";
        cout << endl;
        cout << "++" << R0 << " =" << (++R0);
        cout << endl;
        cout << "--" << R0 << " =" << (--R0);
        cout << endl << endl;

        cout << "+ " << R0 << ": " << (+R0);
        cout << endl;
        cout << "- " << R0 << ": " << (-R0);
        cout << endl;
        R0 = Rational(-R0);
        cout << "+ " << R0 << ": " << (+R0);
        cout << endl;
        cout << "- " << R0 << ": " << (-R0);
        cout << endl << endl;

        cout << R0 << "^4=" << R0.pow(4);
        cout << endl << endl;

        cout << "Inverse: " << R0 << "=" << R0.inverse();
        cout << endl << endl;
    }
}
