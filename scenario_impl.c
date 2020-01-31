#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>


// Function to convert string input to all upper case.
void goUp(char *doUpChar) {
    unsigned long int charLength = strlen(doUpChar);
    char afterConv[charLength];

    for (int iloopvar = 0; iloopvar < charLength; iloopvar++) {
        // Skip newlines
        if (doUpChar[iloopvar] == 10) {
            afterConv[iloopvar] = 0;
        } else {
            afterConv[iloopvar] = toupper(doUpChar[iloopvar]);
        }
    }
    strncpy(doUpChar, afterConv, sizeof(afterConv));
}


int main(void){
    static const char RELATIONSHIP_STATUS[8] = "SERIOUS";
    static const int EXPENSIVE_DINNER = 300;
    static const double BO_DEREK = 11.0;

    bool anyRelationship = false;
    bool seriousRelationship = false;
    bool notTooExpensive = false;
    bool gottaHaveIt = false;
    char inRelationship[2] = {};
    char *relIsSerious = NULL;
    int dinnerDollars = INT_MAX;
    double goesToEleven = 5.0;
    unsigned long int readRes = 0;
    unsigned long int inpLength;

    printf("--- Valentine's Day Plans ---\n\n");
    printf("So are you in a relationship at the moment (answer Y or N)? ");
    scanf(" %c", inRelationship);
    // Scoop up the leftover newline.
    getchar();
    printf("\n");
    goUp(&inRelationship[0]);

    if (!strcmp(inRelationship, "Y")) {
        anyRelationship = true;
        printf("Ok great! Is this a serious relationship or not (answer \"serious\" or \"not serious\")? ");
        getline(&relIsSerious, &inpLength, stdin);
        printf("\n");
        goUp(&relIsSerious[0]);

         if (!strcmp(relIsSerious, RELATIONSHIP_STATUS)) {
            seriousRelationship = true;
            printf("Lookin' good. So, how much are you going to have to spend on dinner (enter an amount in dollars, no cents)? ");
            scanf("%d", &dinnerDollars);
            getchar();
            printf("\n");

            if (dinnerDollars >= EXPENSIVE_DINNER) {
                printf("Holy cow, champagne tastes!! Are you sure this is a serious relationship (answer Y or N)? ");
                //Re-using "inRelationship," since it has a defined size and should be safe.
                scanf(" %c", inRelationship);
                // Scoop up the leftover newline.
                getchar();
                printf("\n");
                goUp(&inRelationship[0]);

                if (!strcmp(inRelationship, "Y")) {
                    notTooExpensive = true;
                } else {
                    printf("Ok, not so serious, but... I mean... lets get a rating on this (from 0.0 to 10.0 (or more...?)): ");
                    scanf("%lf", &goesToEleven);
                    getchar();
                    printf("\n");

                    if (goesToEleven >= BO_DEREK) {
                        gottaHaveIt = true;
                    }
                }
            } else {
                notTooExpensive = true;
            }
        }
    }

    // This could have been done with slightly simpler logic, but we needed a specific number of ANDs and ORs.
    if (anyRelationship && seriousRelationship && (notTooExpensive || gottaHaveIt)) {
        printf("Make reservations for dinner and have fun!\n");
    } else {
        printf("You know what; why not head down to the Winchester, have a pint, and wait for this all to blow over.\n");
    }

    return 0;
}
