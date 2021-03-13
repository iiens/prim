#include <stdlib.h> //!< todo: Valentin
#include <string.h> //!< todo: Valentin
#include "main.h" //!< todo: Valentin

bool back = false; //!< Allow to cancel the current action

//todo: Valentin, translate to english
int main(void)
{
    // Initialisation variables
    Difficulty d; //!< Permet de connaitre la difficulté choisit par l'utilisateur
    Map* map = NULL; //!< Permet de stocker l'etat du jeu
    bool exit = false; //!< ...
    bool endTurn = false; //!< Permet de stocker la detection de la fin d'un tour

    Action act; //!< ...
    Staff s; //!< ...
    Vector2D v; //!< ...
    Machine* m = NULL; //!< ...

    // Initialise interface
    //todo: can fail
    interface_init();

    // Ask difficulty
    d = interface_chooseDifficulty();

    // Creates map
    map = map_create(d);

    // While the user don't want to leave
    while (!exit) {
        // Update
        interface_reload(map);

        // Reset end turn
        endTurn = false;

        while (!endTurn) { // while the user doesn't want the turn to end
            // Demande au joueur de choisir une action
            act = interface_chooseAction();

            // sample to process an action
            // check documentation everything written
            //todo: since you are using err codes, check them
            switch (act) { // NOLINT(hicpp-multiway-paths-covered)
                case ACTION_SHOW_MAP:
                    // Update interface with the new map
                    interface_reload(map);
                    break;
                case ACTION_CANCEL_ACTION: // ignore
                    break;
                case ACTION_EXIT:
                    // Initialize variable to left the game
                    exit = true;
                    endTurn = true;
                    break;
                case ACTION_END_TURN:
                    // Initialize variable to left the turn
                    endTurn = true;
                    break;
                case ACTION_HIRE_FISE:
                    // Call the map function to buy the FISE
                    map_hireFISE(map);
                    break;
                case ACTION_HIRE_FISA:
                    // Call the map function to buy the FISA
                    map_hireFISA(map);
                    break;
                case ACTION_CHANGE_FISA_MODE:
                    // Call The map function to change the mode of production of the FISA
                    // E or DD
                    map_changeProductionFISA();
                    break;
                case ACTION_BUY_MACHINE:
                    do {
                        v = interface_askMachineLocation();
                        // check if it's ok
                    } while (!map_isEmpty(v.x, v.y, map) || back);

                    if (!back) {
                        m = interface_askAddMachine();
                        if(!back){
                            if(map_addMachine(*m, v.x, v.y, map)){
                                // Show the error message because This case don't have a machine
                                // Show the error message because The player don't have the money
                                // TODO OxOrio : Add interface_showError(Error e)
                            }
                        }
                    }
                    break;
                case ACTION_BUY_STAFF:
                    // ask where add staff
                    s = interface_askBuyStaff();
                    if (!back) {
                        if(!map_buyStaff(s, map)){
                            // Show the error message because The player don't have the money
                            // TODO OxOrio : Add interface_showError(Error e)
                        }
                    }
                    break;
                case ACTION_ASK_STAFF_LIST:
                    // Call the interface function to show the list of staff
                    // Player staff list and staff list available
                    interface_showStaffList(map);
                    break;
                case ACTION_UPGRADE_MACHINE:
                    do {
                        v = interface_askMachineLocation();
                        // check if it's ok
                    } while (map_isEmpty(v.x, v.y, map) || back);

                    if (!back) {
                        if(!map_upgradeMachine(v.x, v.y, map)){
                            // Show the error message because This case don't have a machine
                            // Show the error message because The player don't have the money
                            // TODO OxOrio : Add interface_showError(Error e)
                        }
                    }
                    break;
                case ACTION_DESTROY_MACHINE:
                    do {
                        v = interface_askMachineLocation();
                        // check if it's ok
                    } while (map_isEmpty(v.x, v.y, map) || back);

                    if (!back) {
                        if(!map_destroyMachine(v.x, v.y, map)){
                            // Show the error message because This case don't ave a machine
                            // TODO OxOrio : Add interface_showError(Error e)
                        }
                    }
                    break;
                case ACTION_LIST_ACTIONS:
                    interface_list_actions();
                    break;
                case ACTION_LIST_MACHINES:
                    interface_showMachinesList();
                    break;
            }
        }

        // Process end turn
        map_endTurn();
    }

    // Destroy map
    map_destroy(map);

    // Close interface
    interface_close();

    return EXIT_SUCCESS;
}