import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: database.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    keys = []
    persons = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        keys = reader.fieldnames
        for row in reader:
            persons.append(row)

    # TODO: Read DNA sequence file into a variable
    dna_sequence = ""
    with open(sys.argv[2], "r") as file:
        dna_sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    STR_count = []
    for i in range(len(keys)):
        if i == 0:
            continue
        STR_count.append(longest_match(dna_sequence, keys[i]))

    # TODO: Check database for matching profiles
    for person in persons:
        valid = 1
        for j, key in enumerate(keys):
            if j == 0:
                continue
            if int(person[key]) != STR_count[j-1]:
                valid = 0
        if valid == 1:
            return person[keys[0]]
    return "No match"


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


print(main())