# Python3 program to remove invalid parenthesis 

import argparse
import logging, sys
import pdb


# Method checks if character is parenthesis(open 
# or closed) 
def isParenthesis(c):
    return ((c == '(') or (c == ')')) 

# method returns true if contains valid 
# parenthesis 
def isValidString(str):
    cnt = 0
    for i in range(len(str)):
        if (str[i] == '('):
            cnt += 1
        elif (str[i] == ')'):
            cnt -= 1
        if (cnt < 0):
            return False
    return (cnt == 0)
    
# method to remove invalid parenthesis 
def removeInvalidParenthesis(str):
    print(f"starting string: {str}")
    if (len(str) == 0):
        return
        
    # visit set to ignore already visited 
    visit = set()
    
    # queue to maintain BFS
    q = []
    temp = 0
    level = 0
    
    # pushing given as starting node into queue
    q.append(str)
    visit.add(str)

    # pdb.set_trace()
    
    while(len(q)):
        str = q[0]
        q.pop(0)
        if (isValidString(str)):
            print(str)
            
            # If answer is found, make level true 
            # so that valid of only that level 
            # are processed. 
            level = True
        if (level):
            continue
        for i in range(len(str)):
            if (not isParenthesis(str[i])):
                continue
                
            # Removing parenthesis from str and 
            # pushing into queue,if not visited already 
            temp = str[0:i] + str[i + 1:] 
            # temp = str[0:i] + "*" + str[i + 1:] 
            if temp not in visit:
                q.append(temp)
                visit.add(temp)

# Driver Code
expression = "()())()"
removeInvalidParenthesis(expression)
expression = "()v)"
removeInvalidParenthesis(expression)

removeInvalidParenthesis("()())()")
removeInvalidParenthesis("(a)())()")
removeInvalidParenthesis("(")
removeInvalidParenthesis(")")
removeInvalidParenthesis("))))()())()")
removeInvalidParenthesis("))))()())())))")
removeInvalidParenthesis("))))()())())((()))))")
removeInvalidParenthesis("(())))")
removeInvalidParenthesis("()))))")
removeInvalidParenthesis("()))")


# This code is contributed by SHUBHAMSINGH10