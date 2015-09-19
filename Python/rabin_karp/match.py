#!/usr/bin/python

def string_hash(string):
    indices     = range(len(string))
    index_power = zip(indices, reversed(indices))
    return sum([ord(string[i]) * (101 ** p) for (i, p) in index_power])

def update_hash(string, old_hash, new_c):
    to_remove = (ord(string[0])) * (101 ** (len(string) - 1))
    return 101 * (old_hash - to_remove) + ord(new_c)

def rabin_karp(string, pattern):
    l_pattern = len(pattern)
    l_string  = len(string)

    h_pattern = string_hash(pattern)
    h_string      = string_hash(string[0:l_pattern])

    for start in range(0, 1 + l_string - l_pattern):
        current_slice = string[start: start + l_pattern]
        if h_pattern == h_string:
            if current_slice == pattern:
                print("found")
                print(start)
        if (start + l_pattern) < l_string:
            h_string = update_hash(current_slice, h_string, string[start + l_pattern])


rabin_karp('this could be a long sentence, as much as you might want it to be, and we are going to look for things like', ' t')
