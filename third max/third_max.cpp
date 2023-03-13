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

int main()
{
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
  int third_max = third_Max(nums);
  cout << "Third maximum number\n => " << third_max << endl;
  return 0;
}
