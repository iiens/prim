#ifndef PRIM_TRANSLATION_H
#define PRIM_TRANSLATION_H

#include "../data/error.h"
#include "../data/machine.h"
#include "../data/actions.h"
#include "../data/difficulty.h"
#include "../data/case.h"
#include "../utils/structures.h"

#define IS_MACHINE true //!< used in Legend Machine, true is value is machine type

//todo: comment
/*!
 * \typedef Translation
 * \struct Translation_S translation.h "src/view/translation.h"
 *
 * All translations constants
 */
typedef enum Translation_S {
    TRANSLATE_CHOICE_DIFF, //!< difficulty menu header
    TRANSLATE_SCREEN_TOO_SMALL, //!< screen too small message

    TRANSLATE_GAME_NAME, //!< name:
    TRANSLATE_GAME_TURN, //!< turn:
    TRANSLATE_GAME_E, //!< E:
    TRANSLATE_GAME_DD, //!< DD:
    TRANSLATE_GAME_FISE, //!< FISE:
    TRANSLATE_GAME_FISA, //!< FISA:
    TRANSLATE_GAME_FISA_MODE, //!< FISA MODE:
    TRANSLATE_GAME_SCORE, //!< Score:
    TRANSLATE_GAME_GARBAGE, //!< Garbage:

    TRANSLATE_ACTION_LABEL, //!< Action:
    TRANSLATE_GO_BACK_B, //!< go back message

    TRANSLATE_MACHINE_LIST_TITLE, //!< list machines header
    TRANSLATE_ML_COST_TAG, //!< cost
    TRANSLATE_ML_COST_UP_TAG, //!< cost upgrade
    TRANSLATE_ML_COST_DESTROY_TAG, //!< cost destroy

    TRANSLATE_STAFF_LIST_TITLE, //!< list staff header
    TRANSLATE_STAFF_TAG, //!< see below, part of header
    TRANSLATE_TO_TAG, //!< see below, part of header
    TRANSLATE_ON_TAG, //!< see below, part of header
    TRANSLATE_ID_TAG, //!< see below, part of header
    TRANSLATE_OWNED_TAG, //!< number of this staff
    TRANSLATION_LIST_STAFF_INDEX, //!< from when to when
    TRANSLATION_PRESS_ARROW_CHANGE_PAGE, //!< move page message

    TRANSLATE_ACTION_LIST_TITLE, //!< list actions header

    // actions
    TRANSLATE_INPUT_MACHINE_LOCATION, //!< ask Location
    TRANSLATE_INPUT_STAFF, //!< ask Staff ID
    TRANSLATE_INPUT_MACHINE, //!< ask Machine ID
    TRANSLATE_INPUT_ACTION, //!< Action help
    TRANSLATE_INPUT_ORIENTATION, //!< ask orientation

    // legend and view components
    TRANSLATE_LEGEND, //!< Legend:

    TRANSLATE_WIN, //!< win
    TRANSLATE_LOST, //!< loose
} Translation;

/*!
 * Returns the translation of a translation constant
 * @param t: see enum Translation
 * @return the translated or an empty string if there is none
 */
char* translation_get( Translation t );

/*!
 * Returns a translation for a difficulty
 * @param d a difficulty
 * @return the translation
 */
char* translation_getDifficulty( Difficulty d );

/*!
 * Returns action name by enum value
 * @param action action id
 * @return action as a string
 */
char* translation_actionFetchName( Action action );

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

/*!
 * Full name version of translation_fetchCaseTypeName
 * @param t see {@link translation_fetchCaseTypeName}
 * @return see {@link translation_fetchCaseTypeName} */
char* translation_fetchCaseTypeFullName( CaseType t );

/*!
* Full name version of translation_fetchMachineTypeName
* @param s see {@link translation_fetchMachineTypeName}
* @return see {@link translation_fetchMachineTypeName} */
char* translation_fetchMachineTypeFullName( MachineStuff s );

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
List* translation_getLegendMachines(void);

/*!
 * Returns the dictionary of the legend of the directions
 * @return the dictionary
 */
Dictionary* translation_getLegendDirections(void);

/*!
 * Translate a number into 3 characters
 * @param number a number
 * @return char[3] with the number
 */
char* translation_getNumber(int number);

#endif //PRIM_TRANSLATION_H
