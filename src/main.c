#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"

int main( void ) {
    // Variable declarations
    Map* map = NULL; //!< Allows you to store the state of the game
    bool exit = false; //!< flag to detect the choice to close the game
    bool endTurn = false; //!< flag to the end of a tour
    Action act; //!< Allows you to know the action that the player chooses

    // Initializes the game
    map = main_initGame();

    // Check the return of the function
    if ( map == NULL ) {
        // Quit the program because the interface does not work
        return EXIT_SUCCESS;
    }

    // While the user don't want to leave
    while ( !exit ) {
        // Reset end turn
        endTurn = false;

        // While the user doesn't want the turn to end
        while ( !endTurn ) {
            // Interface update
            interface_reload(map);

            // Allows you to ask the player to choose an action
            act = interface_chooseAction();

            // Handling of actions
            endTurn = main_handlingActions(act, map, &exit);
        }

        // Process end turn
        map_endTurn(map);
    }

    // Destroy map
    map_destroy(map);

    // Close interface
    interface_close();

    return EXIT_SUCCESS;
}

Map* main_initGame() {
    Difficulty d; //!< Allows you to know the difficulty chosen by the user
    ErrorCode e; //!< Allows you to get the return of the functions of map.h

    // Initialise interface
    e = interface_init();

    // Check the return of the function
    if ( e != NO_ERROR ) {
        // Show the error message to the console
        printf("%s\n", error_getMessage(e));

        // Quit the function because the interface does not work
        return NULL;
    }

    // Ask difficulty
    d = interface_chooseDifficulty();

    // Creates map
    return map_create(d);
}

bool main_handlingActions(Action act, Map* map, bool* exit) {
    // Variable declarations
    ErrorCode e; //!< Allows you to get the return of the functions of map.h

    switch ( act ) {
        case ACTION_SHOW_MAP:
            // Update interface with the new map
            interface_showMap(map);
            break;
        case ACTION_EXIT:
            // Update variable to left the game
            *exit = true;
            return true;
        case ACTION_END_TURN:
            // Update variable to left the turn
            return true;
        case ACTION_HIRE_FISE:
            // Call the map function to buy the FISE
            e = map_hireFISE(map);

            // Check the return of the function
            if ( e != NO_ERROR ) {
                // Show the error message
                interface_showError(e);
            }
            break;
        case ACTION_HIRE_FISA:
            // Call the map function to buy the FISA
            e = map_hireFISA(map);

            // Check the return of the function
            if ( e != NO_ERROR ) {
                // Show the error message
                interface_showError(e);
            }
            break;
        case ACTION_CHANGE_FISA_MODE:
            // Call The map function to change the mode of production of the FISA
            // E or DD
            e = map_changeProductionFISA(map);

            // Check the return of the function
            if ( e != NO_ERROR ) {
                // Show the error message
                interface_showError(e);
            }
            break;
        case ACTION_BUY_MACHINE:
            // Call the function to buy the machine
            main_buyMachineAction(map);
            break;
        case ACTION_BUY_STAFF:
            // Call the function to buy the staff
            main_buyStaffAction(map);
            break;
        case ACTION_ASK_STAFF_LIST:
            // Call the interface function to show the list of staff
            // Player staff list and staff list available
            interface_showStaffList(map);
            break;
        case ACTION_UPGRADE_MACHINE:
            // Call the function to upgrade machine
            main_upgradeMachineAction(map);
            break;
        case ACTION_DESTROY_MACHINE:
            // Call the function to destroy machine
            main_destroyMachineAction(map);
            break;
        case ACTION_LIST_ACTIONS:
            // Request display of actions
            interface_listActions();
            break;
        case ACTION_LIST_MACHINES:
            // Request the display of machines
            interface_showMachinesList();
            break;
        case ACTION_CANCEL_ACTION: // Ignore
        default:
            break;
    }

    // Reset the action verification variables
    back = false;
    return false;
}

void main_buyMachineAction(Map* map) {
    Vector2D* v = NULL; //!< Used to retrieve the function return from interface.h
    MachineSpec m; //!< Used to retrieve the function return from interface.h
    ErrorCode e; //!< Allows you to get the return of the functions of map.h
    bool check = false; //!< flag to detect the success of certain action

    do {
        // Request the position of the machine
        v = interface_askMachineLocation();

        // Check that the user has not abandoned the action
        if ( !back ) {
            // Ask for the machine to add
            m = interface_askAddMachine();

            // Check that the user has not abandoned the action
            if ( !back ) {
                // Call the map function to add machine
                e = map_addMachine(m.type, m.orientation, v->x, v->y, map);
                // Check the return of the function
                if ( e != NO_ERROR ) {
                    // Show the error message
                    interface_showError(e);
                } else {
                    // update variable to validate the action
                    check = true;
                }
            }
        }
        // While the action is not successful or the user has not abandoned the action
    } while ( !check && !back );

    // Free Vector2D
    if( v != NULL ){
        free(v); v = NULL;
    }
}

void main_buyStaffAction(Map* map) {
    int s; //!< Used to retrieve the function return from interface.h
    ErrorCode e; //!< Allows you to get the return of the functions of map.h
    bool check = false; //!< flag to detect the success of certain action

    do {
        // Ask where add staff
        s = interface_askBuyStaff();

        // Check that the user has not abandoned the action
        if ( !back ) {
            // Call The map function to try to buy a staff member
            e = map_buyStaff(s, map);
            // Check the return of the function
            if ( e != NO_ERROR ) {
                // Show the error message
                interface_showError(e);
            } else {
                // update variable to validate the action
                check = true;
            }
        }
        // While the action is not successful or the user has not abandoned the action
    } while ( !check && !back );

    // Free Staff
    if( s != NULL ){
        free(s); s = NULL;
    }
}

void main_upgradeMachineAction(Map* map) {
    Vector2D* v = NULL; //!< Used to retrieve the function return from interface.h
    ErrorCode e; //!< Allows you to get the return of the functions of map.h
    bool check = false; //!< flag to detect the success of certain action

    do {
        // Request the position of the machine
        v = interface_askMachineLocation();

        // Check that the user has not abandoned the action
        if ( !back ) {
            // Call The map function to improve the machine
            e = map_upgradeMachine(v->x, v->y, map);
            // Check the return of the function
            if ( e != NO_ERROR ) {
                // Show the error message
                interface_showError(e);
            } else {
                // Update variable to validate the action
                check = true;
            }
        }
        // While the action is not successful or the user has not abandoned the action
    } while ( !check && !back );

    // Free Vector2D
    if( v != NULL ){
        free(v); v = NULL;
    }
}

void main_destroyMachineAction(Map* map) {
    Vector2D* v = NULL; //!< Used to retrieve the function return from interface.h
    ErrorCode e; //!< Allows you to get the return of the functions of map.h
    bool check = false; //!< flag to detect the success of certain action

    do {
        // Request the position of the machine
        v = interface_askMachineLocation();

        // Check that the user has not abandoned the action
        if ( !back ) {
            // Call The map function to destroy the machine
            e = map_destroyMachine(v->x, v->y, map);
            // Check the return of the function
            if ( e != NO_ERROR ) {
                // Show the error message
                interface_showError(e);
            } else {
                // Update variable to validate the action
                check = true;
            }
        }
        // While the action is not successful or the user has not abandoned the action
    } while ( !check && !back );

    // Free Vector2D
    if( v != NULL ){
        free(v); v = NULL;
    }
}