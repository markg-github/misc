
import argparse
import logging, sys
import pdb

def threesum(input_array):
    array_length = len(input_array)
    if array_length < 3:
        print("none")
        return
    found_sum = False
    input_array.sort()
    left = 0
    right = array_length-1
    for i in range(1, array_length-2):
        sum = input_array[left] + input_array[i] + input_array[right]
        while sum > 0 and right > i+1:
            right -= 1
            sum = input_array[left] + input_array[i] + input_array[right]
        while sum < 0 and left < i-1:
            left += 1
            sum = input_array[left] + input_array[i] + input_array[right]
        if sum == 0:
            found_sum = True
            break


    if found_sum:
        print(f"{input_array[left]} + {input_array[i]} + {input_array[right]} = 0")
    else:
        print("none")

test_list1 = [1,2,3,4,5,6]
test_list2 = [10,2,3,-40,5,600]
test_list3 = [1000,2,3,5,6,7,8,-40,9,8,7,6,37,6]

threesum(test_list1)
threesum(test_list2)
threesum(test_list3)



                   
