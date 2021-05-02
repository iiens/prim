#include "../nc_headers/interface_ncurses.h"
#include "../nc_headers/interface_ncurses_utils.h"
#include <string.h>

/** Callback on init  */
void* interface_ncurses_chooseActionClosureInit()
{
    if ( interface_ncurses_utils_hasLastMessage() )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_ACTION));
    return NULL;
}

/** check submitted action **/
void* interface_ncurses_chooseActionClosureCheck( char* buff, bool* leave, ErrorCode* error )
{
    const UserActionMapping* m = mapping_getMapping(buff);
    if ( m != NULL ) {
        *leave = true;
        return (void*) &(m->actionID);
    }

    // set error
    *error = ERROR_INVALID_ACTION_SEQUENCE;
    return NULL;
}

Action interface_ncurses_chooseAction()
{
    Action* a = ((Action*) interface_ncurses_showInActionField(interface_ncurses_chooseActionClosureInit,
                                                               interface_ncurses_chooseActionClosureCheck));
    return *a;
}