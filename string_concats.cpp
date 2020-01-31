#include <string>
#include <iostream>
#include <stdio.h>

int main(void){
    std::string word1;
    std::string word2;
    std::string msg;

    word1 = "Hello";
    word2 = "World";

    msg = word1 + " " + word2;

    std::cout << msg << std::endl;
    printf("%s", msg.c_str());

    return 0;
}