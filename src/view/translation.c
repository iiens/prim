#include "../../headers/interface.h"
#include "translation.h"

char* error_getMessage( ErrorCode e )
{
    switch (e) { //todo: fill this with error messages. and use translation.h
        case ERROR_INVALID_ACTION_SEQUENCE:
            return "Wrong actionWindow sequence!";
        case ERROR_INVALID_LOCATION_SEQUENCE:
            return "Coordinates format is \"x,y\"";
        case ERROR_CASE_EMPTY:
            return "Cannot destroy machine, nothing here. Please try again.";
        default:
            return "An unknown error occurred.";
    }
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