//
// Ask machine location
//
#include "../../../../headers/interface.h"
#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"
#include <string.h>

/** Callback on init  */
void* interface_ncurses_askMachineLocationClosureInit()
{
    if ( interface_ncurses_utils_hasLastMessage() )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_MACHINE_LOCATION));
    return NULL;
}

/** Callback on check  */
void* interface_ncurses_askMachineLocationClosureCheck( char* buff, bool* leave, ErrorCode* error )
{
    // he wants to go back
    if ( strcmp(buff, mapping_getBackMapping()->key) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        const int MAX_NUMBER_LENGTH = 8; //!< 2^MAX_NUMBER_LENGTH is the max int length
        int i; //!< position in buffer
        int j = 0; //!< position in each number n1,n2
        int length = (int) strlen(buff); //!< int length
        char* n1; //!< will contains number1
        char* n2; //!< will contains number2
        char* endPtr = NULL; //!<  error pointer
        int v1; //!< first value
        int v2; //!< second value

        if ( length < 10 ) { // not some weird long number
            // creates buffers
            n1 = (char*) calloc(MAX_NUMBER_LENGTH, sizeof(char));
            n2 = (char*) calloc(MAX_NUMBER_LENGTH, sizeof(char));
            // memset(n1,'\0',MAX_NUMBER_LENGTH);
            // memset(n2,'\0',MAX_NUMBER_LENGTH);

            // first number
            for ( i = 0; i < length && buff[i] != ','; i++, j++ ) {
                n1[j] = buff[i];
            }
            // second number
            i++;
            for ( j = 0; i < length; i++, j++ ) {
                n2[j] = buff[i];
            }

            // convert and return
            if ( j != 0 ) { // n2 not empty
                // fetch v1
                v1 = (int) strtol(n1, &endPtr, 10);

                if ( endPtr != NULL ) {
                    v2 = (int) strtol(n2, &endPtr, 10);

                    if ( endPtr != NULL ) {
                        Vector2D* v = (Vector2D*) malloc(sizeof(Vector2D));
                        v->x = v1;
                        v->y = v2;
                        free(n1);
                        free(n2);
                        *leave = true;
                        return v;
                    }
                    interface_close();
                }
            }

            // free
            free(n1);
            free(n2);
        }
    }

    // set error
    *error = ERROR_INVALID_LOCATION_SEQUENCE;
    return NULL;
}

Vector2D* interface_ncurses_askMachineLocation()
{
    Vector2D* v = (Vector2D*) interface_ncurses_showInActionField(interface_ncurses_askMachineLocationClosureInit,
                                                                  interface_ncurses_askMachineLocationClosureCheck);
    return v;
}
