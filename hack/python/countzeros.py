
# countzeros.py


"""

"""

import os
import hashlib
from collections import defaultdict
import csv

import argparse
import logging, sys
import pdb

class Solution:
    def countZero(self, N):
        """
        :type N: int
        :rtype: int, tuple(int)
        """
        def countTo(num):
            for i in range(1, num+1):
                if '0' in str(i):
                    yield i

        gen = countTo(N)
        l = []
        for item in gen:
            l.append(item)
        return l.__len__(), tuple(l)

if __name__ == "__main__":
    """
    Starting block of script
    """

    pdb.set_trace()

    parser = argparse.ArgumentParser(description='count 0 digits from 1 to N')

    # Positional argument
    # parser.add_argument('posarg')

    # Optional argument
    parser.add_argument('-N', type=int, help='N', default="1000")
    # temp_list = list(supported_processors.keys())
    # parser.add_argument('--processor', type=str, help='processor', default=temp_list[0], choices=temp_list)

    # parser.add_argument('-l', '--level', type=int, help='TCB levlel (0,1,2,...)', default=0)

    # Boolean flag
    # parser.add_argument('-v', '--verbose', action='store_true', help='Increase output verbosity')

    args = parser.parse_args()

    N = args.N

    print(N)

    soln = Solution()
    l,t = soln.countZero(N)

    pdb.set_trace()
    



    zero_count = 0
    my_log = 1
    for i in range(N):
        num_string = str(i+1)
        temp_pos = 0
        while True:
            temp_pos = num_string.find('0')
            if temp_pos != -1:
                zero_count += 1
                temp = num_string[:temp_pos] + 'x' + num_string[temp_pos+1:]
                num_string = temp
                print(num_string)
            else:
                break

    print(zero_count)




