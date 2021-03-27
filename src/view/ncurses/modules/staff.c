#include "../../../../headers/interface.h"
#include "../../translation.h"
#include "../interface_ncurses.h"
#include "../interface_ncurses_utils.h"
#include <string.h>

/** init buy staff interface **/
void* interface_ncurses_askBuyStaffClosureInit();

/** input staff **/
void* interface_ncurses_askBuyStaffCheck(char* buff, bool* leave, ErrorCode* error);

Staff* interface_ncurses_askBuyStaff()
{
    Staff* s = ((Staff*) interface_ncurses_showInActionField(
            interface_ncurses_askBuyStaffClosureInit,
            interface_ncurses_askBuyStaffCheck
    ));
    return s;
}

void* interface_ncurses_askBuyStaffClosureInit()
{
    if ( lastMessage == NULL )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_STAFF));
    return NULL;
}

void* interface_ncurses_askBuyStaffCheck(char* buff, bool* leave, ErrorCode* error)
{
    // he wants to go back
    if ( strcmp(buff, BACK_MAPPING) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        const int base = staff_list[0].id; //!< base id
        char* endPtr = NULL; //!< conversion error
        int staffID; //!< staff ID

        staffID = strtol(buff, &endPtr, 10);

        if ( staffID >= base && staffID <= base + NUMBER_OF_STAFFS - 1 ) {
            int index = staffID - base; //!< fetch staff_list index
            // okay
            *leave = true;
            Staff* s = (Staff*) malloc(sizeof(Staff));
            *s = staff_list[index];
            return s;
        }

        // set error
        *error = ERROR_INVALID_STAFF_NUMBER;
        return NULL;
    }
}
