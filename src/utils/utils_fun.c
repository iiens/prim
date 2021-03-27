#include <stdlib.h>
#include "utils_fun.h"

/**
 * Some power function, fix me plz
 */
int utils_power(int n, int e)
{
    int r = 1;
    while ( e > 0 ){
        r *= n;
        e--;
    }
    return r;
}

/**
 * Some aton function
 */
char* utils_intToString(int number)
{
    char* result; //!< result
    int length = 1; //!< number length
    int tmp = number;
    while (tmp >= 10) {
        tmp/=10;
        length++;
    }

    // creates
    result = (char*) malloc((length+1)*sizeof(char));
    result[length] = '\0'; // last

    // fill
    for ( int i = length-1, e = 0; i >= 0; i--, e++ ) {
        if ( e == 0 ){
            result[i] = (char) ((number%10)+'0');
        } else {
            result[i] = (char) ((number/utils_power(number, e))+'0');
        }
    }

    return result;
}