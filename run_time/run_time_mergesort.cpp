#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

void printArray(int* ar, int begin, int end)
{
    for(int i = begin; i <= end; i++)
    {
        cout << ar[i] << " ";
    }

    cout << "\n";
}
void sortArray(int *arr)
{

}

void merge(int *arr, int l, int m, int r)
{
int sz1 = m - l + 1;
int sz2 = r - m;
int NL[sz1];
int NR[sz2];

for (int i = 0; i < sz1; i++)
    NL[i] = arr[l + i];
for (int j = 0; j < sz2; j++)
    NR[j] = arr[m + 1 + j];

    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = l; // Initial index of merged subarray
    while (i < sz1 && j < sz2)
    {
        if (NL[i] <= NR[j])
        {
            arr[k] = NL[i];
            i++;
        }
        else
        {
            arr[k] = NR[j];
            j++;
        }
        k++;
    }
    while (i < sz1)
    {
        arr[k] = NL[i];
        i++;
        k++;
    }
    while (j < sz2)
    {
        arr[k] = NR[j];
        j++;
        k++;
    }
}


int mergeSort(int* arr, int begin, int end)
{

    cout << "Merge Sorting: ";

    printArray(arr, begin, end);
    if(begin != end)
    {
        int begin1 = begin;
        int end1 = (end + begin) / 2;
        int begin2 = end1 + 1;
        int end2 = end;

        mergeSort(arr, begin1, end1);
        mergeSort(arr, begin2, end2);
        merge(arr, begin, end1, end);
    }
    else
    {
        cout << "One List! Do nothing\n";
    }
return 0;
}
int main() {
//    int arr[] = {7,10,1,4,3,9,2};
//    int SIZE = sizeof(arr)/sizeof(int);
//    int mergesort = mergeSort(arr,0, SIZE -1);
//    printArray(arr, 0, SIZE - 1);

    const int SIZE = 1000;
    int arr[SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 100+ 1;
    }
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, SIZE - 1);
    auto stop = chrono::high_resolution_clock::now();

    cout << "Run time: " << chrono::duration_cast<chrono::milliseconds>(stop-start).count()<<endl;
    system("pause");
    return 0;
}
