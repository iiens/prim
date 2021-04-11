#include "../../../../headers/interface.h"
#include "../headers/interface_ncurses.h"
#include "../headers/interface_ncurses_utils.h"
#include <string.h>

MachineStuff lastSelected;

/** init buy machine interface **/
void* interface_ncurses_askBuyMachineClosureInit();

/** init ask orientation interface **/
void* interface_ncurses_askOrientationClosureInit();

/** input machine **/
void* interface_ncurses_askBuyMachineCheck( char* buff, bool* leave, ErrorCode* error );

/** input orientation **/
void* interface_ncurses_askOrientationCheck( char* buff, bool* leave, ErrorCode* error );

MachineSpec interface_ncurses_askAddMachine()
{
    MachineStuff* m = ((MachineStuff*) interface_ncurses_showInActionField(interface_ncurses_askBuyMachineClosureInit,
                                                                           interface_ncurses_askBuyMachineCheck));

    int* rotation = NULL;

    if ( !back ) {
        // save
        lastSelected = *m;
        // ask for rotation
        rotation = (int*) interface_ncurses_showInActionField(interface_ncurses_askOrientationClosureInit,
                                                              interface_ncurses_askOrientationCheck);
    }

    // we need to do that since we use void* and Action* to match this constraint
    if ( !back && rotation != NULL && m != NULL ) {
        MachineSpec machine;
        machine.type = *m;
        machine.rotation = *rotation;
        // free
        free(m);
        free(rotation);
        return machine;
    }

    return (MachineSpec) {};
}

// askBuyMachine

void* interface_ncurses_askBuyMachineClosureInit()
{
    if ( interface_ncurses_utils_hasLastMessage() )
        interface_ncurses_showMessage(translation_get(TRANSLATE_INPUT_MACHINE));
    return NULL;
}

void* interface_ncurses_askBuyMachineCheck( char* buff, bool* leave, ErrorCode* error )
{
    // he wants to go back
    if ( strcmp(buff, mapping_getBackMapping()->key) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        char* endPtr = NULL; //!< conversion error
        int machineID; //!< machine ID

        machineID = (int) strtol(buff, &endPtr, 10);

        if ( endPtr != NULL && machineInfo_isMachineStuffValid(machineID) != -1 ) {
            MachineStuff* m = (MachineStuff*) malloc(sizeof(MachineStuff));
            // okay
            *leave = true;
            *m = machineInfo_getType(machineInfo_getMachineStuff(machineID));
            return m;
        }

        // set error
        *error = ERROR_INVALID_MACHINE_NUMBER;
        return NULL;
    }
}

// askOrientation

void* interface_ncurses_askOrientationClosureInit()
{
    if ( interface_ncurses_utils_hasLastMessage() ) {
        char* message = translation_get(TRANSLATE_INPUT_ORIENTATION);
        char* desc = machineInfo_getDefaultOrientationMessage(machineInfo_getMachineInfoByType(lastSelected));
        int size = (int) strlen(message) + (int) strlen(desc) + 1;
        char* buffer = (char*) malloc(size * sizeof(char));
        sprintf(buffer, "%s %s", message, desc);
        interface_ncurses_showMessage(buffer);
        free(buffer); // free
    }
    return NULL;
}

void* interface_ncurses_askOrientationCheck( char* buff, bool* leave, ErrorCode* error )
{
    // he wants to go back
    if ( strcmp(buff, mapping_getBackMapping()->key) == 0 ) {
        back = true;
        *leave = TRUE;
        return NULL;
    } else {
        char* endPtr = NULL; //!< conversion error
        int rotation = (int) strtol(buff, &endPtr, 10);

        if ( endPtr != NULL && machine_isRotationCorrect(rotation) ) {
            int* result = (int*) malloc(sizeof(int)); //!< store result, no dangling pointer
            *result = rotation;
            *leave = true;
            return result;
        }

        // set error
        *error = ERROR_INVALID_ORIENTATION_NUMBER;
        return NULL;
    }
}
