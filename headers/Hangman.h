#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_TRIES 6
#define ALPHA_SIZE 27
typedef struct Hangman
{
    char *answer;
    char *correct;
    char guessed[ALPHA_SIZE];
    int fails;
    bool gameEnd;
} Hangman;

Hangman HM_CreateHangman(char *answer);

void HM_Guess(Hangman *hangman, char guess);

void HM_Display(Hangman *hangman);

void HM_Free(Hangman *hangman);