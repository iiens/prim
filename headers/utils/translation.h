#ifndef PRIM_TRANSLATION_H
#define PRIM_TRANSLATION_H

    #include "../data/error.h"
    #include "../data/machine.h"
    #include "../data/actions.h"
    #include "../data/difficulty.h"
    #include "../data/case.h"
    #include "../utils/structures.h"

    /*!
     * \typedef Translation
     * \struct Translation_S translation.h "src/view/translation.h"
     *
     * All translations constants
     */
    typedef enum Translation_S {
        TRANSLATE_CHOICE_DIFF,
        TRANSLATE_SCREEN_TOO_SMALL,

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
        TRANSLATE_INPUT_ORIENTATION,

        // legend and view components
        TRANSLATE_LEGEND,
        TRANSLATE_STAFF_TAG,
        TRANSLATE_TO_TAG,
        TRANSLATE_ON_TAG,
        TRANSLATE_ID_TAG,
        TRANSLATE_OWNED_TAG,
    } Translation;

    /*!
     * Returns the translation of a translation constant
     * @param t: see enum Translation
     * @return the translated or an empty string if there is none
     */
    char* translation_get(Translation t);

    /*!
     * Returns a translation for a difficulty
     * @param d a difficulty
     * @return the translation
     */
    char* translation_getDifficulty(Difficulty d);

    /*!
     * Returns action name by enum value
     * @param action action id
     * @return action as a string
     */
    char* translation_actionFetchName( Action action);

    /*!
     * Returns the type of a case
     * @param t type of a case
     * @return the translation or NULL if it's a machine. In such
     * case, use {@link translation_fetchMachineTypeName}
     */
    char* translation_fetchCaseTypeName( CaseType t );

    /*!
     * Returns machine type name
     * @param s stuff of a case
     * @return the translation
     */
    char* translation_fetchMachineTypeName( MachineStuff s );

    /**
     * Full name version of translation_fetchCaseTypeName
     * @param t see {@link translation_fetchCaseTypeName}
     * @return see {@link translation_fetchCaseTypeName} */
    char* translation_fetchCaseTypeFullName( CaseType t );

    /**
    * Full name version of translation_fetchMachineTypeName
    * @param t see {@link translation_fetchMachineTypeName}
    * @return see {@link translation_fetchMachineTypeName} */
    char* translation_fetchMachineTypeFullName( MachineStuff s );

    #define IS_MACHINE true //!< used in Legend Machine, true is value is machine type

    /*!
     * Returns the list of the legend of the machines.
     *
     * Each element is a couple, the key is a boolean
     * <ul><li>true : value is MachineStuff</li>
     * <li>false: machine is a CaseType</li></ul>
     *
     * And value is ether a MachineStuff/CaseType.
     *
     * @return the list
     * @see MachineStuff
     * @see CaseType
     * @see Couple
     */
    List* translation_getLegendMachines();

    /*!
     * Returns the dictionary of the legend of the directions
     * @return the dictionary
     */
    Dictionary* translation_getLegendDirections();

#endif //PRIM_TRANSLATION_H
