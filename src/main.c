#include <stdlib.h> //!< todo: Valentin
#include <string.h> //!< todo: Valentin
#include <stdbool.h> //!< todo : Valentin
#include "main.h" //!< todo: Valentin

bool back = false; //!< Allow to cancel the current action

int main(void)
{
    // Variable declarations
    Difficulty d; //!< Allows you to know the difficulty chosen by the user
    Map* map = NULL; //!< Allows you to store the state of the game
    bool exit = false; //!< flag to detect the choice to close the game
    bool endTurn = false; //!< flag to the end of a tour
    bool check = false; //!< flag to detect the success of certain action

    ErrorCode e; //!< Allows you to get the return of the functions of map.h

    Action act; //!< Allows you to know the action that the player chooses
    Staff s; //!< Used to retrieve the function return from interface.h
    Vector2D v; //!< Used to retrieve the function return from interface.h
    Machine* m = NULL; //!< Used to retrieve the function return from interface.h

    // Initialise interface
    //todo: can fail
    interface_init();

    // Ask difficulty
    d = interface_chooseDifficulty();

    // Creates map
    map = map_create(d);

    // While the user don't want to leave
    while (!exit) {
        // Interface update
        interface_reload(map);

        // Reset end turn
        endTurn = false;

        // While the user doesn't want the turn to end
        while (!endTurn) {
            // Allows you to ask the player to choose an action
            act = interface_chooseAction();

            // Handling of actions
            switch (act) {
                case ACTION_SHOW_MAP:
                    // Update interface with the new map
                    interface_reload(map);
                    break;
                case ACTION_EXIT:
                    // Update variable to left the game
                    exit = true;
                    endTurn = true;
                    break;
                case ACTION_END_TURN:
                    // Update variable to left the turn
                    endTurn = true;
                    break;
                case ACTION_HIRE_FISE:
                    // Call the map function to buy the FISE
                    e = map_hireFISE(map);
                    // Check the return of the function
                    if (e != NO_ERROR) {
                        // Show the error message
                        interface_showError(e);
                    }
                    break;
                case ACTION_HIRE_FISA:
                    // Call the map function to buy the FISA
                    e = map_hireFISA(map);
                    // Check the return of the function
                    if (e != NO_ERROR) {
                        // Show the error message
                        interface_showError(e);
                    }
                    break;
                case ACTION_CHANGE_FISA_MODE:
                    // Call The map function to change the mode of production of the FISA
                    // E or DD
                    e = map_changeProductionFISA();
                    // Check the return of the function
                    if (e != NO_ERROR) {
                        // Show the error message
                        interface_showError(e);
                    }
                    break;
                case ACTION_BUY_MACHINE:
                    do {
                        // Request the position of the machine
                        v = interface_askMachineLocation();
                        // Check that the user has not abandoned the action
                        if (!back) {
                            // Call the map function to add machine
                            e = map_addMachine(*m, v.x, v.y, map);
                            // Check the return of the function
                            if (e != NO_ERROR) {
                                // Show the error message
                                interface_showError(e);
                            }
                            else {
                                // update variable to validate the action
                                check = true;
                            }
                        }
                        // While the action is not successful or the user has not abandoned the action
                    } while (!check || !back);

                    break;
                case ACTION_BUY_STAFF:
                    do {
                        // Ask where add staff
                        s = interface_askBuyStaff();
                        // Check that the user has not abandoned the action
                        if (!back) {
                            // Call The map function to try to buy a staff member
                            e = map_buyStaff(s, map);
                            // Check the return of the function
                            if (e != NO_ERROR) {
                                // Show the error message
                                interface_showError(e);
                            }
                            else {
                                // update variable to validate the action
                                check = true;
                            }
                        }
                        // While the action is not successful or the user has not abandoned the action
                    } while (!check || !back);
                    break;
                case ACTION_ASK_STAFF_LIST:
                    // Call the interface function to show the list of staff
                    // Player staff list and staff list available
                    interface_showStaffList(map);
                    break;
                case ACTION_UPGRADE_MACHINE:
                    do {
                        // Request the position of the machine
                        v = interface_askMachineLocation();
                        // Check that the user has not abandoned the action
                        if (!back) {
                            // Call The map function to improve the machine
                            e = map_upgradeMachine(v.x, v.y, map);
                            // Check the return of the function
                            if (e != NO_ERROR) {
                                // Show the error message
                                interface_showError(e);
                            }
                            else {
                                // Update variable to validate the action
                                check = true;
                            }
                        }
                        // While the action is not successful or the user has not abandoned the action
                    } while (!check || !back);
                    break;
                case ACTION_DESTROY_MACHINE:
                    do {
                        // Request the position of the machine
                        v = interface_askMachineLocation();
                        // Check that the user has not abandoned the action
                        if (!back) {
                            // Call The map function to destroy the machine
                            e = map_destroyMachine(v.x, v.y, map);
                            // Check the return of the function
                            if (e != NO_ERROR) {
                                // Show the error message
                                interface_showError(e);
                            }
                            else {
                                // Update variable to validate the action
                                check = true;
                            }
                        }
                        // While the action is not successful or the user has not abandoned the action
                    } while (!check || !back);
                    break;
                case ACTION_LIST_ACTIONS:
                    // Request display of actions
                    interface_list_actions();
                    break;
                case ACTION_LIST_MACHINES:
                    // Request the display of machines
                    interface_showMachinesList();
                    break;
                case ACTION_CANCEL_ACTION: // Ignore
                default:
                    break;
            }

            back = false;
            check = false;
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