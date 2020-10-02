import re
import math

def main():
    text = input("Text: ")

    # print the number of letters.
    l = l_len(text)

    # print the number of words.
    w = w_len(text)

    # print the number of sentences.
    s = s_len(text)

    # L = Letters ÷ Words × 100

    L = (l / (w + 1) * 100)

    # S = Sentences ÷ Words × 100

    S = (s / (w + 1) * 100)

    # coleman-liau index
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")

    elif index >= 16 or (round(index)) >= 16:
        print("Grade 16+")

    else:
        print("Grade " + str(math.ceil(index)))


    # print(l)
    # print(w)
    # print(s)


# letter count works
def l_len(l):
    count = 0
    for i in range(len(l)):
        if str.isalpha(l[i]):
            count += 1
    return count


# word count works
def w_len(w):
    count = len(w.split())
    return count


# sentence count works
def s_len(s):
    count = len(re.split(r'[.!?]+', s))

    return count - 1


main()
