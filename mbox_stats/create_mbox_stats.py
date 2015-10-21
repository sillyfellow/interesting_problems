#!/usr/bin/python

import re
import argparse
from operator import add


def kilo_bytes(size):
    return round(size / 1024.0, 3)

def in_percentage(n, total):
    if not total:
        return 'nan'
    return str(round(n * 100.0 / total, 2)) + '%'

def my_pretty_print(table, headers):
    divide = '+----------+----------------------------------+--------------+--------------+'
    formatter = '| {:>8} | {:>32} | {:>12} | {:>12} |'

    print divide
    print formatter.format('serial', headers[0] , headers[1], headers[2])
    print divide

    for i, row in enumerate(table):
        print formatter.format(i, row[0], row[1], row[2])
    print divide

def print_message_count_stats(statistics, message_count, summarize=False):
    count_table = [[domain, vals[0]] for domain, vals in statistics.iteritems()]

    # sort based on the count of messages
    count_table.sort(key=lambda x: x[1], reverse=True)
    if summarize:  # we take only the first five, and then summarize the rest.
        count_table = count_table[:5] + [["Others", sum([item[1] for item in count_table[5:]])]]

    # Do the percentage calculation.
    count_table = [[item[0], item[1], in_percentage(item[1], message_count)] for item in count_table]
    my_pretty_print(count_table, ["Domain", "Count", "Percentage"])


def print_message_sizes_stats(statistics, message_size, quote_size):
    # print both sizes in same table.
    # But, sort them based on the size of the message (not the quote/quotation)
    sizes_table = [[domain, kilo_bytes(vals[1]), kilo_bytes(vals[2])] for domain, vals in statistics.iteritems()]
    sizes_table.sort(key=lambda x: x[1], reverse=True)
    my_pretty_print(sizes_table, ["Domain", "Message (Kb)", "Quote (Kb)"])


def print_statistics(statistics):
    message_count, message_size, quote_size = reduce(lambda x, y: map(add, x, y), statistics.values(), [0, 0, 0])
    # We split it into two steps.
    print_message_count_stats(statistics, message_count, True)
    print_message_sizes_stats(statistics, message_size, quote_size)

def update_statistics(stats, message_stats):
    domain, message, quote = message_stats
    stats[domain] = map(add, stats.get(domain, [0, 0, 0]), [1, message, quote])

def extract_domain_from_string(line):
    email = re.search(r'[\w\.-]+@[\w\.-]+', line).group(0)
    return email.split('@')[-1] if email else 'broken_email_domain'

def get_next_message_stats(message):
    in_header = True
    message_size, quote_size = 0, 0
    domain = ''
    for line in message:
        if line.startswith('From: '): # use regex?
            domain = extract_domain_from_string(line)

        # We are out of the header.
        # Note: this might be overwritten again and again.
        if line.isspace():
            in_header = False

        # Skip the quotes / quotations and header
        if in_header:
            continue

        if line.startswith('>'):
            quote_size = quote_size + len(line)
        else:
            message_size = message_size + len(line)

    # We have it
    return domain, message_size, quote_size

def remove_last_new_line(message):
    return message[:-1] if message else []

def process_file(open_file):

    inside  = False
    message = []
    statistics = dict()
    for line in open_file.readlines():

        if line.startswith('From '):
            inside = True
            if message:
                update_statistics(statistics, get_next_message_stats(message))
            message = []

        # if it started with empty lines.
        if not inside:
            continue

        message.append(line)

    # the last one?
    if message:
       update_statistics(statistics, get_next_message_stats(message))

    print_statistics(statistics)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('filename')
    args = parser.parse_args()
    with open(args.filename) as file:
        process_file(file)
