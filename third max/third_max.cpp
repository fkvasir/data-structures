#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int third_Max(vector<int> &nums)
{
    long long first = LLONG_MIN, second = LLONG_MIN, third = LLONG_MIN;

    for (int num : nums)
    {
        if (num > first)
            {
                third = second;
                second = first;
                first = num;
            }
        else if (num > second && num != first)
            {
                third = second;
                second = num;
            }
        else if (num > third && num != second)
            {
                third = num;
            }
    }
    return third == LLONG_MIN ? first : third;
}

void BubbleSort(int arr[], int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = i + 1; j < size; j++)
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

int thirdMax(vector<int>& nums) {
    set<int> maxSet;
    for (const int& num : nums) {
        maxSet.insert(num);
        if (maxSet.size() > 3) {
            maxSet.erase(maxSet.begin());
        }
    }
    return maxSet.size() == 3 ? *maxSet.begin() : *maxSet.rbegin();
}
int ThirdMax2(int arr[], int size)
{
    BubbleSort(arr, size);
    if (size < 3)
        return arr[0];
    return arr[size - 3];
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
    int thirdmax1= thirdMax1(nums);
    cout << "thirdMax1:: " << thirdmax1 << endl;
    int arr_1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
    int len1 = sizeof(arr_1) / sizeof(int);
    int thirdmax2 = ThirdMax2(arr_1, len1);
    cout << "ThirdMax2:: " << thirdmax2 << endl;
    nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
    cout << "thirdMax:: "<<thirdMax(nums) << endl;

    return 0;
}
