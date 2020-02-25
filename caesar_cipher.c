#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

char* caeserCipher(char *inputString, int offset);

int main(void) {
    char* plainText = NULL;
    char* cipherText = NULL;
    int offSetVal = 0;
    long unsigned int uInpLen;
    bool exitCond = false;

    while (!exitCond) {
        printf("Enter the plaintext (enter \"Q\" to exit): ");
        getline(&plainText, &uInpLen, stdin);

        if (!strcmp(plainText, "Q\n")) {
            exitCond = true;
        }

        if (!exitCond) {
            printf("Enter the offset value: ");
            scanf("%d", &offSetVal);
            getchar();

            offSetVal = abs(offSetVal);
            if (offSetVal > 127) {
                offSetVal = 127;
            }
            
            cipherText = caeserCipher(plainText, offSetVal);
            printf("Cipertext: %s\n", cipherText);

            free(cipherText);
            free(plainText);
            cipherText = NULL;
            plainText = NULL;
        }
    }

    return 1;
}

char* caeserCipher(char *inputString, int offset) {
    int iloopvar;
    size_t inpLen = strlen(inputString);
    char* retString = malloc(inpLen);

    memcpy(retString, inputString, inpLen);
    for (iloopvar = 0; iloopvar < ((int)strlen(inputString) - 1); iloopvar++) {
        retString[iloopvar] = retString[iloopvar] + offset;
    }

    return retString;
}