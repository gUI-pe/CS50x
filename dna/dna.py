import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py csv.file dna.text")

    # TODO: Read database file into a variable
    data = []
    filename = sys.argv[1]
    with open(filename) as file:
        reader = csv.DictReader(file)
        for name in reader:
            data.append(name)

    # TODO: Read DNA sequence file into a variable
    dna = []
    dnafile = sys.argv[2]
    with open(dnafile) as file:
        dna = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    agatc = aatg = tatc = 0
    agatc = longest_match(dna, 'AGATC')
    aatg = longest_match(dna, 'AATG')
    tatc = longest_match(dna, 'TATC')

    # TODO: Check database for matching profiles
    for i in range(len(data)):
        if (f"{agatc},{aatg},{tatc}") == (f"{data[i]['AGATC']},{data[i]['AATG']},{data[i]['TATC']}"):
            print(f"{data[i]['name']}")
            return 0

    print("No match")
    return 1


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


main()
