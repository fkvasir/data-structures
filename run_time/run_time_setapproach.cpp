#include <vector>
#include <set>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

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

//int main() {
//    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2};
//    auto start = chrono::high_resolution_clock::now();
//    cout << thirdMax(nums) << endl;
//    auto end = chrono::high_resolution_clock::now();
//    cout << "Elapsed time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ns" << endl;
//
//    return 0;
//}

int main() {
    mt19937 gen(std::random_device{}());
    uniform_int_distribution<int> dist(1, 1000000);

    for (int n = 100; n <= 1000000; n += 90000) {
        vector<int> nums(n);
        for (int i = 0; i < n; i++) {
            nums[i] = dist(gen);
        }
        auto start = chrono::high_resolution_clock::now();
        thirdMax(nums);
        auto end = chrono::high_resolution_clock::now();
        cout << "n = " << n << ", elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds" <<endl;
    }

    return 0;
}
