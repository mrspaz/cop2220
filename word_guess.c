#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

char* getRandomWord(void){
    static char* wordList[5] = {"dog","cat","squirrel","foo","bar"};
    int wordChoice = 0;

    wordChoice = rand()%5;
    return wordList[wordChoice];
}

int main(void) {
    bool exitCond = false;
    bool wordMatch = false;
    char userGuess[100] = {0};
    char *theWord;

    srand(time(NULL));
    printf("Welcome to the Word Guess Game\n");

    while (!exitCond) {
        theWord = getRandomWord();
        wordMatch = false;
        printf("Please enter a guess or QUIT to end the game!\n\n");
        printf("--: ");
        scanf("%s", userGuess);

        while (!wordMatch && !exitCond) {
            if (!strcmp(userGuess, "QUIT")) {
                exitCond = true;
            } else {
                if (!strcmp(userGuess, theWord)) {
                    wordMatch = true;
                    printf("You got it! The word was %s!\nTime for a new word!\n\n", theWord);
                } else {
                    printf("Hmm, not quite. Try again: ");
                    scanf("%s", userGuess);
                }
            }
        }
    }

    return 0;
}
