from cs50 import get_int

def main():
    height = 0
    while height not in range(1, 9):
        height = get_int("Height: ")
    pyramids(height)


def pyramids(height):
    for n in range(1, height + 1):
        print(" " * (height - n), "#" * n, "  ", "#" * n)

main()