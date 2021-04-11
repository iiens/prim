// get all of our variables to translate
#include "../../headers/utils/translation.h"

char* error_getMessage( ErrorCode e )
{
    switch ( e ) { // NOLINT(hicpp-multiway-paths-covered)
        case NO_ERROR:
            break;
        case ERROR:
            return "Some error occurred";
        case ERROR_CASE_MACHINE:
            return "This case is a machine. Please try again.";
        case ERROR_CASE_SOURCE:
            return "This case is a source. Please try again.";
        case ERROR_CASE_GATE:
            return "This case is a gate. Please ry again.";
        case ERROR_CASE_NOT_FOUND:
            return "Case not found";
        case ERROR_NOT_ENOUGH_E:
            return "Not enough E.";
        case ERROR_NOT_ENOUGH_DD:
            return "Not enough DD.";
        case ERROR_NEGATIVE_RESULT:
            return "A value decreased instead of increasing. Invalid internal state.";
        case ERROR_INIT_INTERFACE:
            return "Cannon init interface";
        case ERROR_INIT_NCURSES_INTERFACE:
            return "Cannon init interface, ncurses not supported";
        case ERROR_NO_NCURSES_COLORS_INTERFACE:
            return "Colors aren't supported in this terminal";
        case ERROR_CLOSE_INTERFACE:
            return "Unable to close interface";
        case ERROR_INVALID_ACTION_SEQUENCE:
            return "Wrong actionWindow sequence!";
        case ERROR_INVALID_LOCATION_SEQUENCE:
            return "Coordinates format is \"x,y\"";
        case ERROR_CASE_EMPTY:
            return "No machine here. Please try again.";
        case ERROR_INVALID_STAFF_NUMBER:
            return "Invalid staff ID.";
        case ERROR_INVALID_MACHINE_NUMBER:
            return "Invalid machine ID.";
        case ERROR_INIT_NCURSES_INTERFACE_SIZE:
            return "Cannot init interface, screen too small.";
        case ERROR_INVALID_ORIENTATION_NUMBER:
            return "This is not a valid rotation number.";
    }
    return "Error. Please report it to the developers.";
}

char* translation_getDifficulty(Difficulty d)
{
    switch ( d ) { // NOLINT(hicpp-multiway-paths-covered)
        case DIFFICULTY_EASY:
            return "Difficulty EASY (10x10)";
        case DIFFICULTY_MEDIUM:
            return "Difficulty MEDIUM (20x20)";
        case DIFFICULTY_HARD:
            return "Difficulty HARD (30x30)";
    }
    return NULL;
}

char* translation_get( Translation t )
{
    switch ( t ) { // NOLINT(hicpp-multiway-paths-covered)
        case TRANSLATE_CHOICE_DIFF:
            return "Choose your difficulty";
        case TRANSLATE_SCREEN_TOO_SMALL:
            return "Press q and restart in a bigger screen.";
        case TRANSLATE_GAME_NAME:
            return "Prim, environment line";
        case TRANSLATE_GAME_TURN:
            return "Turn";
        case TRANSLATE_GAME_E:
            return "E";
        case TRANSLATE_GAME_DD:
            return "DD";
        case TRANSLATE_GAME_FISE:
            return "FISE";
        case TRANSLATE_GAME_FISA:
            return "FISA";
        case TRANSLATE_GAME_FISA_MODE:
            return "FISA MODE";
        case TRANSLATE_GAME_STAFFS:
            return "Staffs";
        case TRANSLATE_GAME_SCORE:
            return "Score";
        case TRANSLATE_GAME_GARBAGE:
            return "Garbage";
        case TRANSLATE_ACTION_LABEL:
            return "Action: ";
        case TRANSLATE_GO_BACK_B:
            return "(press b to go back)";
        case TRANSLATE_MACHINE_LIST_TITLE:
            return "List of all machines";
        case TRANSLATE_ML_MACHINE_TAG:
            return "Machine:";
        case TRANSLATE_ML_COST_TAG:
            return ">>> cost: ";
        case TRANSLATE_ML_COST_UP_TAG:
            return " >>> cost upgrade: ";
        case TRANSLATE_ML_COST_DESTROY_TAG:
            return " >>> cost destroy: ";
        case TRANSLATE_STAFF_LIST_TITLE:
            return "List of all staff";
        case TRANSLATION_LIST_STAFF_INDEX:
            return "Staff %d to %d on %d.";
        case TRANSLATION_PRESS_ARROW_CHANGE_PAGE:
            return " Press <- or -> to move to the previous/next page.";
        case TRANSLATE_INPUT_MACHINE_LOCATION:
            return "Submit machine location. Format is \"x,y\" (without \")";
        case TRANSLATE_INPUT_STAFF:
            return "Input staff ID. You could have fetched them using `ls` action. Press `b` to go back.";
        case TRANSLATE_INPUT_MACHINE:
            return "Input machine ID. You could have fetched them using `lm` action. Press `b` to go back.";
        case TRANSLATE_INPUT_ORIENTATION:
            return "Input a rotation (0-3), clockwise.";
        case TRANSLATE_INPUT_ACTION:
            return "Use `help` to get the list of available actions.";
        case TRANSLATE_ACTION_LIST_TITLE:
            return "List of all actions";
        case TRANSLATE_LEGEND:
            return "Legend";
        case TRANSLATE_STAFF_TAG:
            return "Staff";
        case TRANSLATE_TO_TAG:
            return "to";
        case TRANSLATE_ON_TAG:
            return "on";
       case TRANSLATE_ID_TAG:
            return "id";
       case TRANSLATE_OWNED_TAG:
            return "owned";
    }
    return "Error. Please report it to the developers.";
}

char* translation_actionFetchName( Action action )
{
    switch ( action ) { // NOLINT(hicpp-multiway-paths-covered)
        case ACTION_SHOW_MAP:
            return "Show map";
        case ACTION_CANCEL_ACTION:
            return "Cancel action";
        case ACTION_EXIT:
            return "Exit";
        case ACTION_LIST_ACTIONS:
            return "List actions";
        case ACTION_END_TURN:
            return "End turn";
        case ACTION_HIRE_FISE:
            return "Hire FISE";
        case ACTION_HIRE_FISA:
            return "Hire FISA";
        case ACTION_CHANGE_FISA_MODE:
            return "Change FISA mode";
        case ACTION_LIST_MACHINES:
            return "List Machines";
        case ACTION_BUY_MACHINE:
            return "Buy machine";
        case ACTION_BUY_STAFF:
            return "Hire Staff";
        case ACTION_ASK_STAFF_LIST:
            return "List Staffs";
        case ACTION_UPGRADE_MACHINE:
            return "Upgrade machine";
        case ACTION_DESTROY_MACHINE:
            return "Destroy machine";
        case ACTION_SHOW_CASE_RESOURCE:
            return "Show resources";
        case ACTION_SHOW_CASE_GARBAGE:
            return "Show garbage";
    }
    return "Error. Please report it to the developers.";
}

char* translation_fetchCaseTypeName( CaseType t )
{
    switch ( t ) { // NOLINT(hicpp-multiway-paths-covered)
        case CASE_VIDE:
            return " ";
        case CASE_GATE:
            return "G";
        case CASE_SOURCE:
            return "S";
        case CASE_MACHINE:
            return NULL;
    }
    return NULL;
}


char* translation_fetchCaseTypeFullName( CaseType t )
{
    switch ( t ) { // NOLINT(hicpp-multiway-paths-covered)
        case CASE_VIDE:
            return " ";
        case CASE_GATE:
            return "Gate";
        case CASE_SOURCE:
            return "Source";
        case CASE_MACHINE:
            return NULL;
    }
    return NULL;
}

char* translation_fetchMachineTypeName( MachineStuff s )
{
    switch ( s ) { // NOLINT(hicpp-multiway-paths-covered)
        case MS_COLLECTOR:
            return "C";
        case MS_CONVEYOR_BELT:
            return "B";
        case MS_CROSS:
            return "X";
        case MS_RECYCLING_CENTER:
            return "R";
        case MS_JUNKYARD:
            return "J";
    }
    return "Error. Please report it to the developers.";
}

char* translation_fetchMachineTypeFullName( MachineStuff s )
{
    switch ( s ) { // NOLINT(hicpp-multiway-paths-covered)
        case MS_COLLECTOR:
            return "Collector";
        case MS_CONVEYOR_BELT:
            return "Conveyor belt";
        case MS_CROSS:
            return "Cross";
        case MS_RECYCLING_CENTER:
            return "Recycling center";
        case MS_JUNKYARD:
            return "Junkyard";
    }
    return "Error. Please report it to the developers.";
}

List* translation_getLegendMachines()
{
    List* machines = list_createEmpty();
    list_addCoupleInt(machines, !IS_MACHINE, CASE_SOURCE);
    list_addCoupleInt(machines, !IS_MACHINE, CASE_GATE);
    list_addCoupleInt(machines, IS_MACHINE, MS_CONVEYOR_BELT);
    list_addCoupleInt(machines, IS_MACHINE, MS_CROSS);
    list_addCoupleInt(machines, IS_MACHINE, MS_COLLECTOR);
    list_addCoupleInt(machines, IS_MACHINE, MS_RECYCLING_CENTER);
    list_addCoupleInt(machines, IS_MACHINE, MS_JUNKYARD);
    return machines;
}

Dictionary* translation_getLegendDirections()
{
    Dictionary* machines = dictionary_create(8);
    dictionary_addCoupleText(machines, "1", "BOTTOM LEFT");
    dictionary_addCoupleText(machines, "2", "BOTTOM");
    dictionary_addCoupleText(machines, "3", "BOTTOM RIGHT");
    dictionary_addCoupleText(machines, "4", "LEFT");
    dictionary_addCoupleText(machines, "6", "RIGHT");
    dictionary_addCoupleText(machines, "7", "TOP LEFT");
    dictionary_addCoupleText(machines, "8", "TOP");
    dictionary_addCoupleText(machines, "9", "TOP RIGHT");
    return machines;
}