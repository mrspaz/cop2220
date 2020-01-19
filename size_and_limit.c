#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    long unsigned int varIntSize = sizeof(signed int);
    long unsigned int varLongSize = sizeof(signed long int);
    long unsigned int varUnsignedSize = sizeof(unsigned long int);
    long unsigned int varLongLongSize = sizeof(signed long long int);
    long unsigned int varCharSize = sizeof(char);
    long unsigned int varFloatSize = sizeof(float);
    long unsigned int varDoubleSize = sizeof(double);

    printf("Data type sizes (word size is %d bits):\n", CHAR_BIT);
    printf("Size of int is %ld bytes.\n", varIntSize);
    printf(" -Max value: %d Min value: %d\n", INT_MAX, INT_MIN);
    printf("Size of long is %ld bytes.\n", varLongSize);
    printf(" -Max value: %ld Min value: %ld\n", LONG_MAX, LONG_MIN);
    printf("Size of unsigned long is %ld bytes.\n", varUnsignedSize);
    printf(" -Max value: %lu Min value: %d\n", ULONG_MAX, 0);
    printf("Size of long long is %ld bytes.\n", varLongLongSize);
    printf(" -Max value: %lld Min value: %lld\n", LLONG_MAX, LLONG_MIN);
    printf("Size of char is %ld bytes.\n", varCharSize);
    printf(" -Max value: %d Min value: %d\n", CHAR_MAX, CHAR_MIN);
    printf("Size of float is %ld bytes.\n", varFloatSize);
    printf(" -Max value: %f Min value: %f\n", FLT_MAX, FLT_MIN);
    printf("Size of double is %ld bytes.\n", varDoubleSize);
    printf(" -Max value: %lf Min value: %lf\n", DBL_MAX, DBL_MIN);

    /* Declaring any of the above types with the static keyword will not
       change size in memory, only preserve the variables across scopes
       (inside functions, etc.).

       Only int, char, and long can have negative values. Unsigned int/long/etc.
       may have only positive values (hence the "unsigned").
    */

    return 0;
}
