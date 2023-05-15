#include <vector>
#include <set>
#include <iostream>
#include <chrono>
#include <random>
#include <limits>

using namespace std;
using namespace std::chrono;

int thirdMax1(vector<int>& nums) {
    long long first = numeric_limits<long long>::min();
    long long second = numeric_limits<long long>::min();
    long long thirdmax = numeric_limits<long long>::min();

    for (const int& num : nums) {
        if (num > first) {
            thirdmax = second;
            second = first;
            first = num;
        } else if (num > second && num != first) {
            thirdmax = second;
            second = num;
        } else if (num > thirdmax && num != second && num != first) {
            thirdmax = num;
        }
    }

    if (thirdmax != numeric_limits<long long>::min()) {
        return thirdmax;
    }

    return first;
}
//
//int main() {
//    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
//    auto start = chrono::high_resolution_clock::now;
//    cout << thirdMax1(nums) << endl;
//    auto end = chrono::high_resolution_clock::now;
//    cout << "Elapsed time:"  << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms " <<endl;
//    return 0;
//}
int main() {
    mt19937 gen(std::random_device{}());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int n = 100; n <= 1000000; n += 6000) {
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = dist(gen);
        }
        auto start = chrono::high_resolution_clock::now();
        thirdMax1(nums);
        auto end = chrono::high_resolution_clock::now();
        cout << "n = " << n << ", elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" <<endl;
    }

    return 0;
}
