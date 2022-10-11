#include <iostream>
#include <assert.h>

using namespace std;


int main (void)
{
    int i;
    int *iptrarr = new int *[10];
    assert(iptrarr != NULL);

    for (i=0; i<10;++i)
    {

    iptrarr [i] = new int;
    assert(iptrarr[i] != NULL);
    }
    for (i=0;i<10;++i)
    {
        *iptrarr[i] = 9 - i;
    }
    for (i=0; i<10; ++i)
    {
        cout << *iptrarr[i]<<"  ";
    }
    cout << endl;

    for (i=0; i<10; ++i)
    {
        delete iptrarr[i];
    }
    delete[] iptrarr;
return 0;
}

