#include <iostream>

int third_Max()
{
  float first, second, third;
  for (int num : nums)
  {
    while (i < length(list))
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
    return third
  }
}
