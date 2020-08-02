#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//note: this is the body of the program (PROTOTYPE)
int key_test(string s);

//get key. (using command line argument)
int main(int argc, string argv[]) //argc is a counter (2). while argv is an array that is indexed from 0. [0,1], ./[0] [1]
{
    //validate the key
    if (argc == 2) //commandline second position is the key. [1]
    {
        int validity = key_test(argv[1]); //(0) make keytest.
        //printf("%d\n", validity); //tester function.
        // 0 == pass
        if (validity == 0)
        {
            //printf("VALIDITY PASSED\n");
            //set argv[1] to key for ease of use.
            string key = argv[1];
            //get plaintext.
            string p_text = get_string("plaintext: ");
            //encipher.
            for (int i = 'A'; i <= 'Z'; i++)
            {
                key[i - 'A'] = toupper(key[i - 'A']) - i;
            }
            //output "ciphertext: "
            printf("ciphertext: ");
            //body of ciphertext.
            for (int i = 0, n = strlen(p_text); i < n; i++)
            {
                if (isalpha(p_text[i]))
                {
                    p_text[i] = p_text[i] + key[p_text[i] - (isupper(p_text[i]) ? 'A' : 'a')];
                }
                //encrypted message
                printf("%c", p_text[i]);
            }
            printf("\n");
            return 0;
        }
        else if (validity == 1)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        else if (validity == 2)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        else if (validity == 3)
        {
            printf("key must not contain repeated characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
}

//returns 0, 1, 2, or 3. these are error codes.
int key_test(string s)
{
    int i, j, k, k1;
    int n, m, l;
    int sum = 0;
    int sum1 = 0;
    int sum2 = 0;
    //keylength check to 6 characters
    for (i = 0, n = strlen(s); i < n; i++)
    {
        sum += 1;
    }
    //printf("count: %d\n", sum); //length tracker.
    if (sum == 26)
    {
        //printf("return 0.0\n");
        for (j = 0, m = strlen(s); j < m; j++)
        {
            if (isalpha(s[j]) != 0)
            {
                sum1 += 1;
            }
        }
        //printf("alphabet: %d\n", sum1); //alphabet tracker.
        if (sum1 == 26)
        {
            //97(a) - 122(z) (lowercase letters), 65(A) - 90(Z) (uppercase ascii)
            //printf("return 0.1\n");
            int frequency[26] = {0};
            for (k = 0, l = strlen(s); k < l; k++)
            {
                int index = toupper(s[k]) - 'A';
                if (frequency[index] > 0)
                {
                    return 3;
                }
                frequency[index]++;
            }
            return 0;

        }
        else
        {
            //error code 2 = does not pass alphabet test.
            return 2; //this works.
        }
    }
    else
    {
        // error code 1 = does not pass the count.
        return 1; //this works.
    }
}



