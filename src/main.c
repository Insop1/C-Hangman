#include <stdio.h>
#include <Hangman.h>

int main()
{
    Hangman hangman = HM_CreateHangman("A dog.");
    bool error = false;
    
    while(!hangman.gameEnd)
    {
        system("cls");

        char guess[5];
        if(error) 
        {
            printf("Please enter only alphabet characters.\n");
            error = false;
        }

        HM_Display(&hangman);
    
        printf("Guess a character: ");
        scanf("%s", guess);

        if(!isalpha(guess[0]) || strlen(guess) > 1)
        {
            error = true;
            continue;
        }

        HM_Guess(&hangman, guess[0]);
    }
    
    HM_Free(&hangman);
    return 0;
}