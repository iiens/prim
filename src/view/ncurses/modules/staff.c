#include "../../../../headers/interface.h"
#include "../../../../headers/utils/translation.h"
#include "../interface_ncurses.h"
#include "../interface_ncurses_utils.h"
#include <string.h>

/** init buy staff interface **/
void* interface_ncurses_askBuyStaffClosureInit();

/** input staff **/
void* interface_ncurses_askBuyStaffCheck( char* buff, bool* leave, ErrorCode* error );

Staff* interface_ncurses_askBuyStaff()
{
    Staff* s = ((Staff*) interface_ncurses_showInActionField(interface_ncurses_askBuyStaffClosureInit,
                                                             interface_ncurses_askBuyStaffCheck));
    return s;
}

void* interface_ncurses_askBuyStaffClosureInit()
{
    if ( lastMessage == NULL )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_STAFF));
    return NULL;
}

void* interface_ncurses_askBuyStaffCheck( char* buff, bool* leave, ErrorCode* error )
{
    // he wants to go back
    if ( strcmp(buff, BACK_MAPPING) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        char* endPtr = NULL; //!< conversion error
        int staffID; //!< staff ID

        staffID = strtol(buff, &endPtr, 10);

        if ( endPtr != NULL && staff_isIDValid(staffID) == NO_ERROR ) {
            // okay
            *leave = true;
            return (Staff*) staff_getStaffByID(staffID);
        }

        // set error
        *error = ERROR_INVALID_STAFF_NUMBER;
        return NULL;
    }
}
