#include <chrono>
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

void swap(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
void slowsort(int arr[], int i, int j)
{
    if (i>=j)
        return;
    int m = (i + j)/2;
    slowsort(arr, i, m);
    slowsort(arr, m + 1, j);
    if (arr[j]<arr[m])
        swap(&arr[j], &arr[m]);
    slowsort(arr, i, j-1);
}
int main() {
    const int SIZE = 1000;
    int arr[SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100+ 1;
    }
    auto start = chrono::high_resolution_clock::now();
    slowsort(arr, 0, SIZE - 1);
    auto stop = chrono::high_resolution_clock::now();

//    printArray(arr, SIZE);
//    cout << endl;
    cout << "Run time: " << chrono::duration_cast<chrono::microseconds>(stop-start).count()<<"s"<<endl;
    return 0;
}

