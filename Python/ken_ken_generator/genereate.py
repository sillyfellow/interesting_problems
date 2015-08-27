#!/usr/bin/python

from random import randint
import argparse

def print_mat(mat):
    if not mat:
        print "None"
        return
    for row in mat:
        print row

def random_index(num):
    return randint(0, num - 1)

def switch_columns(mat):
    src, dst = random_index(len(mat)), random_index(len(mat))
    for row in mat:
        row[src], row[dst] = row[dst], row[src]

def switch_rows(mat):
    src, dst = random_index(len(mat)), random_index(len(mat))
    mat[src], mat[dst] = mat[dst], mat[src]

def make_matrix_valid(mat, num):
    for row in range(len(mat)):
        mat[row] = [1 + (x % num) for x in mat[row]]

def validate_list_against_set(the_set, the_list, message):
    if the_set != set(the_list):
        print message, the_list
        return False
    return True

def validate_matrix(mat):
    the_set = set(range(1, len(mat) + 1))
    # We could avoid going through EACH column and ROW (using the 'and'.. but
    # then we'll know only the first wrong row, nothing which comes afterwards.
    row_vals = [validate_list_against_set(the_set, row, "Broken row:") for row in mat]
    col_vals = [validate_list_against_set(the_set, [row[col] for row in mat], "Broken col: ") for col in range(len(mat))]
    set_vals = set (row_vals + col_vals)
    return False if False in set_vals else True

def generate(num):
    matrix = [range(x, x + num) for x in range(0, num)]
    make_matrix_valid(matrix, num)
    for iteration in range(num * num):
        switch_columns(matrix)
        switch_rows(matrix)
    return matrix if validate_matrix(matrix) else None

def kenkenify(board):
    print_mat( board)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate kenken board of size n')
    parser.add_argument('-N', '--size', type=int, help='size of the board')
    args = parser.parse_args()
    if args.size:
        kenkenify(generate(args.size))
    else:
        print parser.print_help()
