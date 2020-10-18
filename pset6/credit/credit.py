import re

def main():
    # If the card number is valid, ask the kind of card
    while True:
        card_number = input("Number: ")
        if card_number.isdigit():
            if is_valid(card_number):
                print(which_kind(card_number))
            else:
                print("INVALID")
            break

def is_valid(card_number):
    # Multiply every digit by 2, starting with the number’s second-to-last digit
    numbers = str(card_number)[::-1]
    first_part = ([int(numbers[n]) * 2 for n in range(1, len(numbers), 2)])
    for number in first_part:
        if int(number) > 9:
            first_part.extend((str(number)[0], str(number)[1]))

    # Add those products’ digits together.
    first_total = (sum([int(number) for number in first_part if int(number) < 10]))

    # Add the sum to the sum of the digits that weren’t multiplied by 2.
    second_total = sum([int(numbers[n]) for n in range(0, len(numbers), 2)])
    total = int(first_total) + int(second_total)

    # If the total’s last digit is 0, the number is valid!
    if not total % 10:
        return True
    return False

def which_kind(card_number):
    if re.search("^3[47]", card_number):
        return "AMEX"
    elif re.search("^3[47]", card_number) or re.search("^5[12345]", card_number):
        return "MASTERCARD"
    elif card_number.startswith("4"):
        return "VISA"
    return "INVALID"


main()