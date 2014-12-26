#!/usr/bin/python

def is_square_matrix(matrix, n):
    # none is a matrix
    if not matrix and n == 0:
        return True
    # all elements are lists
    if not reduce(lambda x, y: x and type(y) is list, matrix, True):
        return False
    # each column has the same count (as the number of rows)
    col_counts = [len(row) for row in matrix]
    return (n == len(col_counts)) and (col_counts.count(len(matrix)) == len(matrix))


def rotate(matrix, n):
    if not is_square_matrix(matrix, n):
        return
    n1 = n - 1
    for i in range(0, 1 + n1 / 2):
        for j in range(0, n / 2):
            tmp                    = matrix[i][j]
            matrix[i][j]           = matrix[j][n1 - i]
            matrix[j][n1 - i]      = matrix[n1 - i][n1 - j]
            matrix[n1 - i][n1 - j] = matrix[n1 - j][i]
            matrix[n1 - j][i]      = tmp


def rotate_recursive(matrix, n):
    if not is_square_matrix(matrix, n):
        return
    n1 = n - 1
    def dive_into_matrix(i, j, val, l):
        oldval = matrix[i][j]
        matrix[i][j] = val
        return oldval if l == 0 else dive_into_matrix(j, n1 - i, oldval, l - 1)
    for i in range(0, 1 + n1 / 2):
        for j in range(0, n / 2):
            matrix[i][j] = dive_into_matrix(j, n1 - i, matrix[i][j], 2)


def print_mat(matrix):
    for row in matrix:
        print row
    print 42* '*'

print 'recursive rotation, this way -> '
a = [[11, 12, 13], [21, 22, 23], [31, 32, 33]]
print_mat(a)
rotate_recursive(a, 3)
print_mat(a)
rotate_recursive(a, 3)
print_mat(a)
rotate_recursive(a, 3)
print_mat(a)
rotate_recursive(a, 3)
print_mat(a)
rotate_recursive(a, 3)
print_mat(a)

print 'normal rotation, this way <- '
a = [[11, 12, 13], [21, 22, 23], [31, 32, 33]]
print_mat(a)
rotate(a, 3)
print_mat(a)
rotate(a, 3)
print_mat(a)
rotate(a, 3)
print_mat(a)
rotate(a, 3)
print_mat(a)
rotate(a, 3)
print_mat(a)
