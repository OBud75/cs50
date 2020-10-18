from sys import argv
from sys import exit
from csv import DictReader

def main():
    # Usage
    if len(argv) != 3 or not argv[1].endswith(".csv") or not argv[2].endswith(".txt"):
        exit("Usage: python dna.py data.csv sequence.txt")

    # Open files
    with open(argv[1], "r") as csv_file:
        data = DictReader(csv_file)
        with open(argv[2], "r") as txt_file:
            sequence = txt_file.read()

        # Create dict with dna patterns as keys and successive repetition as value
        counts = {}
        for pattern in data.fieldnames[1:]:
            counts[pattern] = most_successives_repetitions(sequence, pattern)

        # Check with which person the dna match
        for row in data:
            if all(counts[pattern] == int(row[pattern]) for pattern in counts):
                exit(row["name"])
        exit("No match")

def most_successives_repetitions(sequence, pattern):
    # Best successive repetition
    max_successives_repetitions = 0

    # Check all the sequence
    for i in range(len(sequence)):

        # New repetition
        count = 0
        while True:

            # Define index and check if pattern matches
            start = i + len(pattern) * count
            stop = start + len(pattern)
            if sequence[start:stop] == pattern:
                count += 1
            else:
                break

        # Update best if new > best
        if count > max_successives_repetitions:
            max_successives_repetitions = count
    return max_successives_repetitions


main()
