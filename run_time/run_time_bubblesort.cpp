#include <chrono>
#include <iostream>
#include <vector>
#include <random>
#include <set>


using namespace std;
using namespace std::chrono;



void BubbleSort(int arr[])
{
    int n;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (arr[i] > arr[j])
      {
            int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

int thirdMax2(int arr[])
{
    int n;
    BubbleSort(arr);
    if (n < 3)
        return arr[0];
    return arr[n - 3];
}

int main() {
    mt19937 gen(std::random_device{}());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int n = 100; n <= 1000; n += 900) {
        int arr[n];
        for (int i = 0; i < n; i++) {
            arr[i] = dist(gen);
        }
        auto start = chrono::high_resolution_clock::now();
        thirdMax2( arr);
        auto end = chrono::high_resolution_clock::now();
        cout << "n = " << n << ", elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds" <<endl;
    }

    return 0;
}
//int main() {
//    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
//    auto start = chrono::high_resolution_clock::now;
//    cout << ThirdMax2(arr) << endl;
//    auto end = chrono::high_resolution_clock::now;
//    cout << "Elapsed time:" << chrono::duration_cast<chrono::microseconds>(end - start).count()<< " ms " <<endl;
//    return 0;
//}

