#ifndef PRIM_TRANSLATION_H
#define PRIM_TRANSLATION_H

    #include "../data/error.h"
    #include "../data/machine.h"
    #include "../data/actions.h"

    /*!
     * \typedef Translation
     * \struct Translation_S translation.h "src/view/translation.h"
     *
     * All translations constants
     */
    typedef enum Translation_S {
        TRANSLATE_CHOICE_DIFF,
        TRANSLATE_SCREEN_TOO_SMALL,
        TRANSLATE_DIF_E,
        TRANSLATE_DIF_M,
        TRANSLATE_DIF_H,

        TRANSLATE_GAME_NAME,
        TRANSLATE_GAME_TURN,
        TRANSLATE_GAME_E,
        TRANSLATE_GAME_DD,
        TRANSLATE_GAME_FISE,
        TRANSLATE_GAME_FISA,
        TRANSLATE_GAME_FISA_MODE,
        TRANSLATE_GAME_STAFFS,
        TRANSLATE_GAME_SCORE,
        TRANSLATE_GAME_GARBAGE,

        TRANSLATE_ACTION_LABEL,
        TRANSLATE_GO_BACK_B,

        TRANSLATE_MACHINE_LIST_TITLE,
        TRANSLATE_ML_MACHINE_TAG,
        TRANSLATE_ML_COST_TAG ,
        TRANSLATE_ML_COST_UP_TAG,
        TRANSLATE_ML_COST_DESTROY_TAG,

        TRANSLATE_STAFF_LIST_TITLE,
        TRANSLATION_LIST_STAFF_INDEX,
        TRANSLATION_PRESS_ARROW_CHANGE_PAGE,

        TRANSLATE_ACTION_LIST_TITLE,

        // actions
        TRANSLATE_INPUT_MACHINE_LOCATION,
        TRANSLATE_INPUT_STAFF,
        TRANSLATE_INPUT_MACHINE,
        TRANSLATE_INPUT_ACTION,
    } Translation;

    /**
     * Returns the translation of a translation constant
     * @param t: see enum Translation
     * @return the translated or an empty string if there is none
     */
    char* translation_get(Translation t);

    /**
     * Convenience method, return machine name
     * @param s machine stuff
     * @return translation
     */
    char* translation_getMachineType(MachineStuff s);

    /**
     * Returns action name by enum value
     * @param action action id
     * @return action as a string
     */
    char* actions_utils_fetchAction(Action action);

#endif //PRIM_TRANSLATION_H
