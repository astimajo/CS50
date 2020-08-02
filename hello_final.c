#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("What is your name?\n"); //prompts the user to type his/her name.
    printf("Hello, %s\n", name); //note: % + s or f or i etc is like a placeholder.
}