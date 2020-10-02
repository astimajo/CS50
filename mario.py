def main():

    # Getting input from the user. (1-8 only)
    height = get_height_int()

    # Pyramid
    for row in range(height):
        # Left section of the pyramid.
        for col in range(height - row):
            print(" ", end="")
        for hash in range(height - col):
            print("#", end="")

        # 2 spaces (dots) in middle of 2 pyramids.
        for space in range(2):
            print(" ", end="")

        # Right section of the pyramid.
        for hash in range(height - col):
            print("#", end="")

        print("")



def get_height_int():
    while True:
        height = int(input("Height: "))

        if height in range(1, 9):
            return height


main()