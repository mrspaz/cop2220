#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char word1[6] = {};
    char word2[6] = {};
    char msg[12] = {};

    strncpy(&word1[0], "Hello", 5);
    strncpy(&word2[0], "World", 5);

    strncat(&msg[0], word1, 6);
    strncat(&msg[0], " ", 1);
    strncat(&msg[0], word2, 6);

    printf("%s\n", msg);

    return 0;
}
