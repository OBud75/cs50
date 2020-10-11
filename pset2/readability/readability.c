#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

float get_letters_number(string text);
float get_words_number(string text);
float get_sentences_number(string text);
float get_grade(float letters_number, float words_number, float sentences_number);


int main(void)
{
    string text = get_string("Text: ");
    float letters_number = get_letters_number(text);
    float words_number = get_words_number(text);
    float sentences_number = get_sentences_number(text);
    int grade = (get_grade(letters_number, words_number, sentences_number));

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }

    else
    {
        printf ("Grade %d\n", grade);
    }
}


float get_letters_number(string text)
{
    float letters_number = 0;
    for (int i= 0, n= strlen(text); i< n; i++)
    {
        if (isalpha(text[i]))
        {
            letters_number +=1;
        }
    }
    return letters_number;
}


float get_words_number(string text)
{
    float words_number = 1;
    for (int i= 0, n= strlen(text); i< n; i++)
    {
        if (isblank(text[i]) && isalpha(text[i+ 1]))
        {
            words_number +=1;
        }
    }
    return words_number;
}


float get_sentences_number(string text)
{
    float sentences_number= 0;
    for (int i = 0, n = strlen(text); i<n; i++)
    {
        if (text[i]== '?' || text[i] == '!' || text[i]== '.')
        {
            sentences_number+= 1;
        }
    }
    return sentences_number;

}


float get_grade(float letters_number, float words_number, float sentences_number)
{
    double L = (letters_number / words_number) * 100;
    double S = (sentences_number / words_number) * 100;

    float grade = (0.0588 * L) - (0.296 * S) - 15.8;
    grade = round(grade);
    return grade;
}