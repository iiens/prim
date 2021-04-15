#include "../../../../headers/interface.h"
#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"
#include <string.h>

/** init buy staff interface **/
void* interface_ncurses_askBuyStaffClosureInit();

/** input staff **/
void* interface_ncurses_askBuyStaffCheck( char* buff, bool* leave, ErrorCode* error );

int interface_ncurses_askBuyStaff()
{
    int* s = ((int*) interface_ncurses_showInActionField(interface_ncurses_askBuyStaffClosureInit,
                                                         interface_ncurses_askBuyStaffCheck));
    // pass
    if ( s != NULL ) {
        int staff_id = *s;
        free(s);
        return staff_id;
    }

    // back
    return -1;
}

void* interface_ncurses_askBuyStaffClosureInit()
{
    if ( interface_ncurses_utils_hasLastMessage() )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_STAFF));
    return NULL;
}

void* interface_ncurses_askBuyStaffCheck( char* buff, bool* leave, ErrorCode* error )
{
    // he wants to go back
    if ( strcmp(buff, mapping_getBackMapping()->key) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        char* endPtr = NULL; //!< conversion error
        int staffID; //!< staff ID

        staffID = (int) strtol(buff, &endPtr, 10);

        if ( endPtr != NULL && staff_isIDValid(staffID) != -1 ) {
            int* result = (int*) malloc(sizeof(int)); //!< returned result
            *result = staffID;
            // okay
            *leave = true;
            return result;
        }

        // set error
        *error = ERROR_INVALID_STAFF_NUMBER;
        return NULL;
    }
}
