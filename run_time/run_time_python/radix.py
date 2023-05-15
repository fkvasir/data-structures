import random
import time


def radix_sort(arr):
    # determine the maximum number of digits in the input array
    max_digits = len(str(max(arr)))
    # perform counting sort on each digit, starting from the least significant digit
    for i in range(max_digits):
        # initialize the count array and the output array
        count = [0] * 10
        output = [0] * len(arr)
        # count the occurrences of each digit in the input array
        for j in range(len(arr)):
            digit = arr[j] // (10**i) % 10
            count[digit] += 1
        # calculate the running sum of the count array
        for j in range(1, 10):
            count[j] += count[j - 1]
        # place each element in its sorted position in the output array
        for j in range(len(arr) - 1, -1, -1):
            digit = arr[j] // (10**i) % 10
            output[count[digit] - 1] = arr[j]
            count[digit] -= 1
        # copy the sorted array back to the input array
        arr = output
    return arr


# generate a random input array of size 50000
arr = [random.randint(0, 1000000) for _ in range(2000000)]

# measure the time it takes to sort the input array using radix sort
start_time = time.time()
sorted_arr = radix_sort(arr)
end_time = time.time()

# print the runtime in seconds
print("Runtime: ", end_time - start_time, "seconds")
