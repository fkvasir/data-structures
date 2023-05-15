

#include <iostream>

using namespace std;

int preset[] = {25, 88, 3, 38, 20, 71, 55, 56, 50, 105};
int hk_linear[17] = {0};
int hk_quadratic[17] = {0};
int hk_double[17] = {0};
int probes_linear = 0, probes_quadratic = 0, probes_double = 0;

int linear(int key)
{
    return key % 17;
}

int quadratic(int key, int i)
{
    return (key + i*i) % 17;
}

int hdouble(int key, int i)
{
    int h1 = key % 17;
    int h2 = 13 - (key % 13);
    return (h1 + i*h2) % 17;
}

void insert_linear(int key)
{
    int i = 0;
    int index = linear(key);
    while (hk_linear[index] != 0)
    {
        probes_linear++;
        i++;
        index = linear(key + i);
    }
    hk_linear[index] = key;
}

void insert_quadratic(int key)
{
    int i = 0;
    int index = quadratic(key, i);
    while (hk_quadratic[index] != 0)
    {
        probes_quadratic++;
        i++;
        index = quadratic(key, i);
    }
    hk_quadratic[index] = key;
}

void insert_double(int key)
{
    int i = 0;
    int index = hdouble(key, i);
    while (hk_double[index] != 0)
    {
        probes_double++;
        i++;
        index = hdouble(key, i);
    }
    hk_double[index] = key;
}

int main()
{
    // linear probing
    for (int i = 0; i < 10; i++)
    {
        insert_linear(preset[i]);
    }

    // quadratic probing
    for (int i = 0; i < 10; i++)
    {
        insert_quadratic(preset[i]);
    }

    // double hashing
    for (int i = 0; i < 10; i++)
    {
        insert_double(preset[i]);
    }

    // Print
    cout << "Linear Probing | Quadratic Probing | Double Hashing\n";
    for (int i = 0; i < 17; i++)
    {
        cout << i<< ": "<< hk_linear[i]<< " | "<< hk_quadratic[i]<< " | "<< hk_double[i]<< endl;
    }
    cout << "Total probes: (Linear | Quadratic | Double)\n"<< probes_linear<< " | "<< probes_quadratic<< " | "<< probes_double<< endl;


    return 0;
}

