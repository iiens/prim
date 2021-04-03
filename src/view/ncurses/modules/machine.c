#include "../../../../headers/interface.h"
#include "../../../../headers/utils/translation.h"
#include "../interface_ncurses.h"
#include "../interface_ncurses_utils.h"
#include <string.h>

/** init buy machine interface **/
void* interface_ncurses_askBuyMachineClosureInit();

/** input staff **/
void* interface_ncurses_askBuyMachineCheck(char* buff, bool* leave, ErrorCode* error);

MachineStuff interface_ncurses_askAddMachine()
{
    MachineStuff* m = ((MachineStuff*) interface_ncurses_showInActionField(
            interface_ncurses_askBuyMachineClosureInit,
            interface_ncurses_askBuyMachineCheck
    ));
    // we need to do that since we use void* and Action* to match this constraint
    MachineStuff machine = *m;
    free(m);
    return machine;
}

void* interface_ncurses_askBuyMachineClosureInit()
{
    if ( lastMessage == NULL )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_MACHINE));
    return NULL;
}

void* interface_ncurses_askBuyMachineCheck(char* buff, bool* leave, ErrorCode* error)
{
    // he wants to go back
    if ( strcmp(buff, BACK_MAPPING) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        const int base = machine_list[0].type; //!< base id
        char* endPtr = NULL; //!< conversion error
        int machineID; //!< machine ID

        machineID = strtol(buff, &endPtr, 10);

        if ( machineID >= base && machineID <= base + NUMBER_OF_MACHINES - 1 ) {
            int index = machineID - base; //!< fetch machine_list index
            // okay
            *leave = true;
            MachineStuff* m = (MachineStuff*) malloc(sizeof(MachineStuff));
            *m = machine_list[index].type;
            return m;
        }

        // set error
        *error = ERROR_INVALID_STAFF_NUMBER;
        return NULL;
    }
}
