#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//transfer from cs50 sandbox(test).
//Note: You might want to cast your one or more values to float before performing division when calculating L and S!
//command line arguments probably not needed.
//functions.
int l_len(string l);
int w_len(string w);
int s_len(string s);

int main(void)
{
    string text = get_string("Text: ");

    //print the number of letters.
    int l = l_len(text);
    //printf("%d letter(s)\n", l);

    //print the number of words.
    int w = w_len(text);
    //printf("%d word(s)\n", w + 1);

    //print the number of sentences.
    int s = s_len(text);
    //printf("%d sentence(s)\n", s);

    //L = Letters ÷ Words × 100
    float L = ((float) l / (float)(w + 1) * 100);

    //S = Sentences ÷ Words × 100
    float S = ((float) s / (float)(w + 1) * 100);

    //coleman-liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16 || (round(index)) >= 16) //note: there are iterations of round index where 15.5 becomes 16.
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index)); //%.0f removes decimal tenths and etc.
    }

}

int l_len(string l)
{
    int sum = 0;
    for (int i = 0, n = strlen(l); i < n; i++)
    {
        //test each character in the array if alphabet or not
        if (isalpha(l[i]) != 0)
        {
            sum += 1;
        }
    }
    return sum;
}

int w_len(string w)
{
    int sum = 0, i;
    //text[] automatically makes an array from the input strings i is the index count
    for (i = 0; w[i] != '\0'; i++) //reminder again: i makes the loop move.
    {
        if (w[i] == ' ' && w[i + 1] != ' ') //note && specifies the requirements for each array element to limit the count to such.
        {
            sum++;
        }
    }
    return sum;
}

int s_len(string s)
{
    int sum = 0, i;
    //text[] automatically makes an array from the input strings i is the index count
    for (i = 0; s[i] != '\0'; i++) //reminder again: i makes the loop move.
    {
        if ((s[i] == '.' || s[i] == '!' || s[i] == '?') && (s[i + 1] != '.' || s[i] != '!' || s[i] != '?'))
            //note && specifies the requirements for each array element to limit the count to such.
        {
            sum++;
        }
    }
    return sum;
}
