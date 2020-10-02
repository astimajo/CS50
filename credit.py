def main():
    credit_card_no = not_zero()

    if valid_check(credit_card_no):
        credit_card_comp_check(credit_card_no)
    else:
        print("INVALID")


def not_zero():
    while True:
        credit_card_no = int(input("Number: "))

        if credit_card_no > 0:
            return credit_card_no


def valid_check(credit_card_no):
    length = find_len(credit_card_no)
    # print(length)
    if length == 13 or length == 15 or length == 16 and luhn_check(credit_card_no):
        return True


def find_len(n):
    length = 0
    # note // is floor division meaning no decimals.
    while n > 0:
        n = n // 10
        length = length + 1
    return length


# The problem is down here.
def luhn_check(cc_no):
    count = 0
    # Transform cc_no to string first so that len can count it.
    for i in range(len(str(cc_no))):
        if i % 2 == 0:
            count += cc_no % 10
        else:
            digit = 2 * (cc_no % 10)
            count += digit // 10 + digit % 10
        # Floor Division operator 
        cc_no //= 10

    return count % 10 == 0


# possibly no problems here.
def credit_card_comp_check(cc_no):
    if 34e13 <= cc_no < 35e13 or 37e13 <= cc_no < 38e13:
        print("AMEX")

    elif 51e14 <= cc_no < 56e14:
        print("MASTERCARD")

    elif 4e12 <= cc_no < 5e12 or 4e15 <= cc_no < 5e15:
        print("VISA")

    else:
        print("INVALID")


main()
