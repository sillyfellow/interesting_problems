#!/usr/bin/python

from random import randint
import argparse

class Kenken:
    def show(self):
        for row in self.matrix:
            print row

    def __init__(self, size):
        self.matrix = self.generate_matrix(size)
        self.shuffle_matrix()
        if not Kenken.validate_matrix(self.matrix):
            raise "Error - invalid matrix"

    def randindex(self):
        return randint(0, self.size() - 1)

    def switch_columns(self):
        src, dst = self.randindex(), self.randindex()
        for row in self.matrix:
            row[src], row[dst] = row[dst], row[src]

    def switch_rows(self):
        src, dst = self.randindex(), self.randindex()
        self.matrix[src], self.matrix[dst] = self.matrix[dst], self.matrix[src]


    def size(self):
        return len(self.matrix)

    def generate_matrix(self, num):
        matrix = [range(x, x + num) for x in range(0, num)]
        return [[1 + (x % num) for x in row] for row in matrix]


    @staticmethod
    def validate_list_against_set(the_set, the_list, message):
        if the_set != set(the_list):
            print message, the_list
            return False
        return True

    @staticmethod
    def validate_matrix(mat):
        the_set = set(range(1, len(mat) + 1))
        # We could avoid going through EACH column and row (using the 'and'.. but
        # then we'll know only the first wrong row, nothing which comes afterwards.
        row_vals = [Kenken.validate_list_against_set(the_set, row, "Broken row:") for row in mat]
        col_vals = [Kenken.validate_list_against_set(the_set, [row[col] for row in mat], "Broken col: ") for col in range(len(mat))]
        set_vals = set (row_vals + col_vals)
        return False if False in set_vals else True

    def shuffle_matrix(self):
        for iteration in range(randint(self.size(), 2 * self.size())): # What is the optimal number?
            self.switch_columns()
            self.switch_rows()


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate kenken board of size n')
    parser.add_argument('-N', '--size', type=int, help='size of the board')
    args = parser.parse_args()
    if args.size:
        kenken = Kenken(args.size)
        kenken.show()
        # kenkenify(generate(args.size))
    else:
        print parser.print_help()
