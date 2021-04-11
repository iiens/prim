#include <stdlib.h> //!< malloc
#include <stdio.h> //!< sprintf
#include "../../headers/utils/utils_fun.h" //!< .c header

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