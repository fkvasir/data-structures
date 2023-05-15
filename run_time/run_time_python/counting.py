import random
import time


def counting_sort(arr):
    # find the range of the input elements
    k = max(arr) + 1
    # initialize the count array with zeros
    count = [0] * k
    # count the occurrences of each element in the input array
    for i in arr:
        count[i] += 1
    # calculate the running sum of the count array
    for i in range(1, k):
        count[i] += count[i - 1]
    # initialize the output array with zeros
    output = [0] * len(arr)
    # place each element in its sorted position in the output array
    for i in range(len(arr) - 1, -1, -1):
        output[count[arr[i]] - 1] = arr[i]
        count[arr[i]] -= 1
    return output


# generate a random input array of size 500
arr = [random.randint(0, 1000) for _ in range(2000000)]

# measure the time it takes to sort the input array using counting sort
start_time = time.time()
sorted_arr = counting_sort(arr)
end_time = time.time()

# print the runtime in seconds
print("Runtime: ", end_time - start_time, "seconds")
.
