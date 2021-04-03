// get all of our variables to translate
#include "../../headers/utils/translation.h"

char* error_getMessage(ErrorCode e)
{
    switch ( e ) {
        case NO_ERROR:
            break;
        case ERROR:
            return "Some error occurred";
        case ERROR_CASE_MACHINE:
            return "case is a machine"; //todo: what ?
        case ERROR_CASE_SOURCE:
            return "case is a source"; //todo: what ?
        case ERROR_CASE_GATE:
            return "case is a gate"; //todo: what ?
        case ERROR_CASE_NOT_FOUND:
            return "Case not found";
        case ERROR_NOT_ENOUGH_E:
            return "Not enough E.";
        case ERROR_NOT_ENOUGH_DD:
            return "Not enough DD.";
        case ERROR_NEGATIVE_RESULT:
            return "Result is negative"; //todo: what ?
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
        case ERROR_CASE_EMPTY: //todo: empty for destroy, ... ?
            return "No machine here. Please try again.";
        case ERROR_INVALID_STAFF_NUMBER:
            return "Invalid staff ID.";
        case ERROR_INVALID_MACHINE_NUMBER:
            return "Invalid machine ID.";
        case ERROR_INIT_NCURSES_INTERFACE_SIZE:
            return "Cannot init interface, screen too small.";
        default:
            return "An unknown error occurred.";
    }
    return "Error. Please report it to the developers.";
}

char* translation_get(Translation t)
{
    switch ( t ) {
        case TRANSLATE_CHOICE_DIFF:
            return "Choose your difficulty";
        case TRANSLATE_SCREEN_TOO_SMALL:
            return "Press q and restart in a bigger screen.";
        case TRANSLATE_DIF_E:
            return "Difficulty EASY (10x10)";
        case TRANSLATE_DIF_M:
            return "Difficulty MEDIUM (20x20)";
        case TRANSLATE_DIF_H:
            return "Difficulty HARD (30x30)";
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
            return "Input staff ID. You can fetch them using `ls` action. Press `b` to go back.";
        case TRANSLATE_INPUT_MACHINE:
            return "Input machine ID. You can fetch them using `lm` action. Press `b` to go back.";
        case TRANSLATE_INPUT_ACTION:
            return "Use `help` to get the list of available actions.";
        case TRANSLATE_ACTION_LIST_TITLE:
            return "List of all actions";
        default:
            return "";
    }
}

char* translation_getMachineType(MachineStuff s)
{
    switch ( s ) {
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
        default:
            return "Unknown machine";
    }
}

char* actions_utils_fetchAction(Action action)
{
    switch ( action ) {
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
        default:
            return "Unknow command";
    }
}