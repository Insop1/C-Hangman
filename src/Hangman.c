#include <Hangman.h>

static char* HM_FilterAnswer(char *answer)
{
    char *filtered = (char *)malloc(strlen(answer) + 1); 
    if (filtered == NULL) {
        perror("memory failed for filtered\n");
        exit(1);
    }
    int j = 0;
    for(int i = 0; i < strlen(answer); i++)
    {
        if(isalpha(answer[i]) || answer[i] == ' ')
        {
            filtered[j++] = answer[i];
        }
    }
    filtered[j] = '\0';
    return filtered;
}

Hangman HM_CreateHangman(char *answer)
{
    Hangman hangman = {
        .fails = 1,
        .gameEnd = false,
        .guessed = { '\0' }
    };
    
    hangman.answer = HM_FilterAnswer(answer);
    hangman.correct = (char*)malloc(strlen(hangman.answer) + 1);
    if (hangman.correct == NULL) 
    {
        printf("memory fail.\n");
        exit(1);
    }
    for (int i = 0; i < strlen(hangman.answer); i++) 
    {
        hangman.correct[i] = (hangman.answer[i] == ' ') ? ' ' : '_';
    }
    hangman.correct[strlen(hangman.answer)] = '\0';
    return hangman;
}

void HM_GuessedWrongPush(char guessed[], char letter)
{
    for(int i = 0; i < 26; i++)
    {
        if(guessed[i] == letter)
        {
            return;
        } 
        if(guessed[i] == '\0') 
        {
            guessed[i] = letter;
            return;
        }
    }
}

void HM_Guess(Hangman *hangman, char guess)
{
    char letter = tolower(guess);

    if (!isalpha(letter)) 
    {
        printf("Please enter an alphabet letter.\n");
        return;
    }

    bool wasWrong = true;
    for(int i = 0; i < strlen(hangman->answer); i++)
    {
        if(tolower(hangman->answer[i]) == letter)
        {
            hangman->correct[i] = hangman->answer[i];
            wasWrong = false;
        }
    }
    if(wasWrong)
    {
        hangman->fails++;
        HM_GuessedWrongPush(hangman->guessed, letter);
    }

    if (hangman->fails > MAX_TRIES)
    {
        printf("Answer: %s\n", hangman->answer);
        printf("You lost!\n");
        hangman->gameEnd = true;
        return;
    }   
    for (int i = 0; i < strlen(hangman->correct); i++)
    {
        if (hangman->correct[i] == '_')
        {
            return;
        }
    }

    printf("Answer: %s\n", hangman->answer);
    printf("YOU WON!!!\n");
    hangman->gameEnd = true;
}

void HM_Display(Hangman *hangman)
{
    printf("WRONG LETTERS: [");
    for(int i = 0; hangman->guessed[i] != '\0'; i++)
    {
        printf(" %c ", hangman->guessed[i]);
    }
    printf("]\n=================\n");

    printf("[ATTEMPTS: %d / %d]\n", hangman->fails, MAX_TRIES);
    printf("%s\n", hangman->correct);
}

void HM_Free(Hangman *hangman)
{
    free(hangman->answer);
    free(hangman->correct);
}
