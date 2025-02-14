
import argparse
import logging, sys
import pdb

import test_lists


class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

def detect_ll_cycle(head):
    pdb.set_trace()
    if head == None or head.next == None:
        return False
    # two pointers traversing the list at different "speeds",
    # say one vs. two nodes at a time. if current (or next?)
    # nodes are ever equal, then cycle
    pslow = head.next
    pfast = head.next.next
    is_cycle = False
    while pslow != None and pfast != None:
        if pslow == pfast:
            is_cycle = True
            break
        pslow = pslow.next
        pfast = pfast.next
        if pfast == None:
            break
        pfast = pfast.next

    return is_cycle

mylist = []

listid = 1
# list[index] = test_lists.get_test_list(index)
mylist.append((test_lists.get_test_list(listid), listid))

listid = 2
# list[index] = test_lists.get_test_list(index)
mylist.append((test_lists.get_test_list(listid), listid))

listid = 3
# list[index] = test_lists.get_test_list(index)
mylist.append((test_lists.get_test_list(listid), listid))

listid = 4
# list[index] = test_lists.get_test_list(index)
mylist.append((test_lists.get_test_list(listid), listid))

for tpl in mylist:
    is_cycle = detect_ll_cycle(tpl[0])
    print(f"cycle in list {tpl[1]}: {is_cycle}")

