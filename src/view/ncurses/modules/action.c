#include "../../../../headers/interface.h"
#include "../../translation.h"
#include "../interface_ncurses.h"
#include "../interface_ncurses_utils.h"
#include <string.h>

/** Callback on init  */
void* interface_ncurses_chooseActionClosureInit()
{
    if (lastMessage == NULL)
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_ACTION));
    return NULL;
}

/** check submitted action **/
void* interface_ncurses_chooseActionClosureCheck(char* buff, bool* leave, ErrorCode* error)
{
    for (int i = 0; i < USER_MAPPING_SIZE; ++i) {
        if(strcmp(buff, user_mapping[i].key) == 0){ //same
            *leave = true;
            // return acton
            Action* a = (Action*) malloc(sizeof(Action));
            *a = user_mapping[i].actionID;
            return a;
        }
    }
    // set error
    *error = ERROR_INVALID_ACTION_SEQUENCE;
    return NULL;
}

Action interface_ncurses_chooseAction()
{
    Action* a = ((Action*) interface_ncurses_showInActionField(
            interface_ncurses_chooseActionClosureInit,
            interface_ncurses_chooseActionClosureCheck
    ));
    // we need to do that since we use void* and Action* to match this constraint
    Action action = *a;
    free(a);
    return action;
}