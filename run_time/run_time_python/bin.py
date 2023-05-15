import random
import time


def bin_sort(arr, num_bins):
    # calculate the range of the input array
    arr_range = max(arr) - min(arr) + 1
    # calculate the size of each bin
    bin_size = arr_range // num_bins + 1
    # initialize the bins
    bins = [[] for _ in range(num_bins)]
    # place each element in its corresponding bin
    for i in arr:
        bin_idx = (i - min(arr)) // bin_size
        bins[bin_idx].append(i)
    # sort each bin and concatenate them
    sorted_arr = []
    for bin in bins:
        sorted_arr.extend(sorted(bin))
    return sorted_arr


# generate a random input array of size 10000
arr = [random.randint(0, 1000) for _ in range(1000000)]

# measure the time it takes to sort the input array using bin sort with 10 bins
start_time = time.time()
sorted_arr = bin_sort(arr, 10)
end_time = time.time()

# print the runtime in seconds
print("Runtime: ", end_time - start_time, "seconds")
.
