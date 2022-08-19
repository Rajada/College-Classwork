#include "ExpandArray.h"

int main()
{
    int a[3] = {1,2,3};
    int b[3] = {4,5,6};
    ExpandArray<int> ea(a,3,-3,0.5);
    ExpandArray<int> ea2(b,3,-3,0.5);
    ExpandArray<int> *eaptr = &ea;

    cout << ea(-3,-1);

    cout << "DONE!" << endl;
    cin.get();

    return 0;
}
