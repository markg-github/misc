

from enum import Enum, auto

import pdb

class Direction(Enum):
    UP = auto()
    DOWN = auto()
    LEFT = auto()
    RIGHT = auto()

Di = Direction


class The2048Bonacci():

    def __init__(self, game_area):
        self.game_area = game_area
        self.width = len(self.game_area[0])
        self.height = len(self.game_area)
        self.fibonacci = [1, 1]

    def _init_fibonacci(self):
        max_val = max(
            max(fib_val for fib_val in line)
            for line in self.game_area
        )
        pdb.set_trace()
        while self.fibonacci[-1] < max_val:
            self.fibonacci.append(self.fibonacci[-1] + self.fibonacci[-2])
        if self.fibonacci[-1] > max_val:
            raise Exception(
                f"This value is not in the Fibonacci sequence: {max_val}"
            )
        self.fibonacci.append(self.fibonacci[-1] + self.fibonacci[-2])
        pdb.set_trace()

    def get_tile(self, x, y):
        return self.game_area[y][x]

    def set_tile(self, x, y, fib_value):
        self.game_area[y][x] = fib_value

    def _iterate_on_line_coords(self, pushing_direction):
        if pushing_direction in (Di.DOWN, Di.UP):
            coord_ys = list(range(self.height))
            if pushing_direction == Di.UP:
                coord_ys = coord_ys[::-1]
            for coord_x in range(self.width):
                line_coords = [
                    (coord_x, coord_y) for coord_y in coord_ys
                ]
                yield line_coords
        else:
            coord_xs = list(range(self.width))
            if pushing_direction == Di.LEFT:
                coord_xs = coord_xs[::-1]
            for coord_y in range(self.height):
                line_coords = [
                    (coord_x, coord_y) for coord_x in coord_xs
                ]
                yield line_coords

    def _do_fibonacci_fusing(self, fibo_vals):
        nb_total_vals = len(fibo_vals)
        fibo_vals = list(filter(None, fibo_vals))
        processed_fibo_vals = []

        if fibo_vals:
            prev_val = fibo_vals[-1]
            for cur_val in fibo_vals[-2::-1]:
                if prev_val != 0:
                    if prev_val + cur_val in self.fibonacci:
                        prev_val = prev_val + cur_val
                        cur_val = 0
                    processed_fibo_vals.insert(0, prev_val)
                prev_val = cur_val
            if prev_val != 0:
                processed_fibo_vals.insert(0, prev_val)

        missing_zeros = [0] * (nb_total_vals - len(processed_fibo_vals))
        return  missing_zeros + processed_fibo_vals

    def process_push(self, pushing_direction):
        self._init_fibonacci()
        for line_coords in self._iterate_on_line_coords(pushing_direction):
            fibo_vals = [
                self.get_tile(*coord) for coord in line_coords
            ]
            fused_fibo_vals = self._do_fibonacci_fusing(fibo_vals)
            for (x, y), fibo_val in zip(line_coords, fused_fibo_vals):
                self.set_tile(x, y, fibo_val)

    def get_description(self):
        str_lines = []
        for line in self.game_area:
            str_line = " ".join(
                [
                    f"{fib_val:2d}" for fib_val in line
                ]
            )
            str_lines.append(str_line)
        return "\n".join(str_lines)


## Some tests

def main():

    game_area = [
        [2, 2,2,2],
        [2, 2,2,2],
        [2, 2,2,2],
        [2, 2,2,2]
    ]
    the_2048_bonacci = The2048Bonacci(game_area)
    the_2048_bonacci.process_push(Di.DOWN)
    the_2048_bonacci.process_push(Di.RIGHT)
    the_2048_bonacci.process_push(Di.UP)
    the_2048_bonacci.process_push(Di.LEFT)
    print("----")
    pdb.set_trace()
    
    game_area = [
        [1,1,1,1],
        [1,1,1,1],
        [1,1,1,1],
        [1,1,1,1]
    ]
    the_2048_bonacci = The2048Bonacci(game_area)
    the_2048_bonacci.process_push(Di.DOWN)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [2, 2,2,2],
        [2, 2,2,2]
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    the_2048_bonacci.process_push(Di.RIGHT)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [2, 2,2,2],
        [2, 2,2,2]
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    the_2048_bonacci.process_push(Di.UP)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [2, 2,2,2],
        [2, 2,2,2],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    the_2048_bonacci.process_push(Di.LEFT)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [2, 2,2,2],
        [2, 2,2,2],
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    # Rule 1
    # Numbers move as far as possible in the pushing direction.
    game_area = [
        [2, 0, 0, 0],
        [0, 0, 13, 0],
        [0, 0, 0, 0],
        [5, 0, 0, 0],
    ]
    the_2048_bonacci = The2048Bonacci(game_area)
    the_2048_bonacci.process_push(Di.DOWN)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [2, 0, 0, 0],
        [5, 0, 13, 0],
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    # Rule 2
    # When two consecutive numbers in the Fibonacci sequence
    # are pushed one on another, they fuse into the next number.
    game_area = [
        [0, 0, 1, 2],
        [1, 0, 1, 0],
        [0, 8, 5, 0],
        [0, 5, 8, 0],
    ]
    the_2048_bonacci = The2048Bonacci(game_area)
    the_2048_bonacci.process_push(Di.RIGHT)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [0, 0, 0, 3],
        [0, 0, 0, 2],
        [0, 0, 0, 13],
        [0, 0, 0, 13],
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    # Rule 3
    # Fusing orders are resolved in the backward direction of the push.
    # A fused number can not be fused once again in the same turn.
    game_area = [
        [0, 1, 2, 3],
        [0, 3, 2, 1],
        [0, 0, 0, 0],
        [0, 5, 3, 5],
    ]
    the_2048_bonacci = The2048Bonacci(game_area)
    the_2048_bonacci.process_push(Di.RIGHT)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [0, 0, 1, 5],
        [0, 0, 3, 3],
        [0, 0, 0, 0],
        [0, 0, 5, 8],
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")
    the_2048_bonacci.process_push(Di.RIGHT)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [0, 0, 1, 5],
        [0, 0, 3, 3],
        [0, 0, 0, 0],
        [0, 0, 0, 13],
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")

    # Rule 4
    # Numbers can move to a square that has just been emptied by a fusing.
    game_area = [
        [1, 0, 0, 0],
        [1, 0, 0, 0],
        [1, 0, 0, 0],
        [1, 0, 0, 0],
    ]
    the_2048_bonacci = The2048Bonacci(game_area)
    the_2048_bonacci.process_push(Di.UP)
    print(the_2048_bonacci.get_description())
    game_area_test = [
        [2, 0, 0, 0],
        [2, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
    ]
    assert the_2048_bonacci.game_area == game_area_test
    print("----")


if __name__ == "__main__":
    main()
