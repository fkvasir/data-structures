#include <iostream>
#include <assert.h>

using namespace std;

struct ext
{
    int value;
    struct ext *nextext;
};

int main()
{
    ext ext_1, ext_2, ext_3;
    ext *temp;

    ext_1.nextext = &ext_2;
    ext_2.nextext = &ext_3;
    ext_3.nextext = &ext_1;
    
    int size;
    cout << "Enter size: ";
    cin >> size; 
    
    int *intarr[size];
    int i;
    
   
    
    for (i = 0; i < size; ++i)
    {
        intarr[i] = new int;
        assert(intarr[i] != NULL);

        *intarr[i] = i + 1;
    }

    ext_1.value = *intarr[0];
    ext_2.value = *intarr[1];
    ext_3.value = *intarr[2];

    temp = &ext_1;
    

    for (i = 0; i < size; ++i)
    {
        cout << temp->value << "  ";

        temp = temp->nextext;
    }

    for (i = 0; i < size; ++i)
    {
        delete intarr[i];
    }

    return 0;
}
