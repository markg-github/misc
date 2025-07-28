
def merge_sorted(l1, l2):
    merged_list = []
    len1 = len(l1)
    len2 = len(l2)
    index1 = 0
    index2 = 0
    
    while True:
        if index1 == len1 or index2 == len2:
            break
        if l1[index1] < l2[index2]:
            merged_list.append(l1[index1])
            index1 += 1
        else:
            merged_list.append(l2[index2])
            index2 += 1

    # this is the subtle part. why does it work?
    # two cases: we're at the end of l1 or at the end of l2
    # in either case one of the extends won't do anything and
    # the other will extend with values that are all higher
    merged_list.extend(l1[index1:])
    merged_list.extend(l2[index2:])

    return merged_list


mylist1 = [1,9,3,7,5,7,6,5]
mylist2 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]

mylist1.sort()
mylist2.sort()

my_merged = merge_sorted(mylist1, mylist2)

print(mylist1)
print(mylist2)
print(my_merged)

