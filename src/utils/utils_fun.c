#include <stdlib.h>
#include <stdio.h>
#include "utils_fun.h"

/**
 * Some power function, fix me plz
 */
int utils_power( int n, int e )
{
    int r = 1;
    while ( e > 0 ) {
        r *= n;
        e--;
    }
    return r;
}

/**
 * Some aton function
 */
char* utils_intToString( int number )
{
    char* result; //!< result
    int length = 1; //!< number length
    int tmp = number;
    // get number size
    while ( tmp >= 10 ) {
        tmp /= 10;
        length++;
    }

    // creates a buffer and print number into it
    result = (char*) malloc((length + 1) * sizeof(char));
    sprintf(result, "%d", number);

    return result;
}