#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

void ShellSort(int arr[], size_t size)
{
	int gap = size;
	while (gap>1)
	{
		gap = gap / 3 + 1;
		for (size_t idx = gap; idx < size; ++idx)
		{
			int temp = arr[idx];
			int end = idx - gap;
			while (end >= 0 && temp<arr[end])
			{
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = temp;
		}
	}
}


void PrintArray(int *array,size_t size)
{
	for (size_t idx = 0; idx < size; ++idx)
	{
		cout << array[idx] << " ";
	}
	cout << endl;
}

int main()
{
//	int arr[] = { 21,25,49,25,16,8};
//	ShellSort(arr, sizeof(arr) / sizeof(arr[0]));
//	PrintArray(arr, sizeof(arr) / sizeof(arr[0]));
    const int SIZE = 100000;
    int arr[SIZE];
    srand(time(NULL));

    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 100+ 1;
    }
    auto start = chrono::high_resolution_clock::now();
    ShellSort(arr, SIZE-1);
    auto stop = chrono::high_resolution_clock::now();

    cout << "Run time: " << chrono::duration_cast<chrono::milliseconds>(stop-start).count()<<endl;

	system("pause");
	return 0;
}

