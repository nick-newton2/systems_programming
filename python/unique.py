#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]
    -c      Prefix lines by the number of occurences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines
By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    ''' Count the line frequencies from the data in the specified stream while
    ignoring case if specified. '''
    freq = {}

    for line in stream:
        line = line.rstrip()
        if ignore_case:
            line = line.lower()
        if line in freq.keys():
            freq[line] += 1
        else:
            freq[line] = 1
    return freq

def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):
    ''' Display line information based on specified parameters:
    - occurences:  if True, then prefix lines with number of occurrences
    - duplicates:   if True, then only print duplicate lines
    - unique_only:  if True, then only print unique lines
    '''
    if duplicates:
        unique = []

        for key in frequencies:
            if frequencies[key] == 1:
                unique.append(key)
        for item in unique:
            frequencies.pop(item)

    elif unique_only:
        duplicate = []

        for key in frequencies:
            if frequencies[key] > 1:
                duplicate.append(key)

        for item in duplicate:
            frequencies.pop(item)
    if occurrences:
        for line, frequency in frequencies.items():
            print(f'{frequency:>7} {line}')
    else:
        for line in frequencies:
            print(f'{line}')


def main():
    ''' Process command line arguments, count frequencies from standard input,
    and then print lines. '''

    occurrences = False
    duplicates = False
    ignore_case = False
    unique_only = False

    arguments = sys.argv[1:]
    while arguments and arguments[0].startswith('-'):
        argument = arguments.pop(0)
        if argument == '-h':
            usage(0)
        elif argument == '-c':
            occurrences = True
        elif argument == '-d':
            duplicates = True
        elif argument == '-i':
            ignore_case = True
        elif argument == '-u':
            unique_only = True
        else:
            usage(0)
    frequencies = count_frequencies(ignore_case=ignore_case)
    print_lines(frequencies, occurrences=occurrences, duplicates=duplicates, unique_only=unique_only)

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
