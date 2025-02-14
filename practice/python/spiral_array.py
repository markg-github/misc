
import argparse
import logging, sys
import pdb

from enum import Enum, auto

class Direction(Enum):
    UP = auto()
    DOWN = auto()
    LEFT = auto()
    RIGHT = auto()


def spiral_array(thesize):
    print(f"size = {thesize}")
    if thesize == 1:
        theresult = [1]
        return theresult
    theresult = [[0 for _ in range(thesize)] for _ in range(thesize)]
    thedirection = Direction.RIGHT
    num_elements = thesize*thesize
    thevalue = 1
    therow = thecol = 0
    rowbump = 0
    colbump = 1
    maxcol = thesize - 1
    maxrow = thesize - 1
    mincol = 0
    minrow = 1
    for i in range(0, num_elements):
        theresult[therow][thecol] = thevalue
        if thedirection == Direction.RIGHT and thecol == maxcol:
            thedirection = Direction.DOWN
            rowbump = 1
            colbump = 0
            maxcol -= 1
        elif thedirection == Direction.DOWN and therow == maxrow:
            thedirection = Direction.LEFT
            rowbump = 0
            colbump = -1
            maxrow -= 1
        elif thedirection == Direction.LEFT and thecol == mincol:
            thedirection = Direction.UP
            rowbump = -1
            colbump = 0
            mincol += 1
        elif thedirection == Direction.UP and therow == minrow:
            thedirection = Direction.RIGHT
            rowbump = 0
            colbump = 1
            minrow += 1
        thevalue += 1
        therow += rowbump
        thecol += colbump
        
        print(f"row = {therow}, col = {thecol}")


    print(f"{theresult}")

spiral_array(2)
spiral_array(3)
spiral_array(30)
