#include <stdio.h>
#include <cs50.h>

// custom functions.
bool luhn_check(long long cc_no);
int find_len(long long n);
bool valid_check(long long credit_card_no);
void credit_card_comp_check(long long cc_no);


//prompting the user for credit card number.
int main(void)
{
    long long credit_card_no;
    // makes sure number is greater than 0.
    do
    {
        credit_card_no = get_long_long("Number: ");
    }
    while (credit_card_no < 0);
    // repeats if not right.
    if (valid_check(credit_card_no) == true)
    {
        credit_card_comp_check(credit_card_no);
    }
    else
    {
        printf("INVALID\n");
    }
}
// checks the validity of the card by finding its length based on specs in cs50 site.
bool valid_check(long long credit_card_no)
{
    int len = find_len(credit_card_no); // find_len is defined below.
    return (len == 13 || len == 15 || len == 16) && luhn_check(credit_card_no);
}

//this function finds the length of the long integer n - an input or any long int.
int find_len(long long n)
{
    int len;
    for (len = 0; n != 0; n /= 10, len ++);
    return len;
}

// This function executes luhn's algorithm. (every 2 digits).
bool luhn_check(long long cc_no)
{
    int sum = 0;
    for (int i = 0; cc_no != 0; i++, cc_no /= 10)
    {
        if (i % 2 == 0) //every 2 not part of second to last sequence downward
        {
            sum += cc_no % 10;
        }
        else
        {
            int digit = 2 * (cc_no % 10);
            sum += digit / 10 + digit % 10; //separates 2 digit products.
        }
    }
    return (sum % 10) == 0; //if bool returns true and satisfies valid check for 2 functions proceed to company detection.
}

// Determines which credit card company is applicable to cc_no.
void credit_card_comp_check(long long cc_no)
{
    if ((cc_no >= 34e13 && cc_no < 35e13) || (cc_no >= 37e13 && cc_no < 38e13))
    {
        printf("AMEX\n");
    }
    else if (cc_no >= 51e14 && cc_no < 56e14)
    {
        printf("MASTERCARD\n");
    }
    else if ((cc_no >= 4e12 && cc_no < 5e12) || (cc_no >= 4e15 && cc_no < 5e15))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
