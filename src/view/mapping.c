#include "../../headers/data/mapping.h"
#include <string.h>

/** @see interface_chooseAction, count of available actions */
#define USER_MAPPING_SIZE 15 //!< to iterates user_mapping

/*!
 * This array length is predetermined by {@link USER_MAPPING_SIZE}
 * constant in interface.h.
 *
 * @see UserActionMapping, all mappings
 */
const UserActionMapping user_mapping[] = {
        // actions related to the game in general
        {ACTION_SHOW_MAP,         "m"}, //!< show map with m
        {ACTION_SHOW_CASE_RESOURCE,  "x"}, //!< show case resources on x
        {ACTION_SHOW_CASE_GARBAGE,  "g"}, //!< show case garbage on g
        {ACTION_END_TURN,         "n"}, //!< end turn with n
        {ACTION_CANCEL_ACTION,    "b"}, //!< cancel action with b
        {ACTION_LIST_ACTIONS,     "help"}, //!< list actions with help
        {ACTION_EXIT,             "q"}, //!< exit with q

        // hire
        {ACTION_HIRE_FISE,        "he"}, //!< hire FISE with he
        {ACTION_HIRE_FISA,        "ha"}, //!< hire FISA with ha
        {ACTION_CHANGE_FISA_MODE, "c"}, //!< change mode with c

        // actions related to the units
        {ACTION_LIST_MACHINES,    "lm"}, //!< list machines with lm
        {ACTION_BUY_MACHINE,      "bm"}, //!< buy machine with bm
        {ACTION_BUY_STAFF,        "bs"}, //!< hire Staff with bs
        {ACTION_ASK_STAFF_LIST,   "ls"}, //!< list Staff with ls

        // actions related to the machines
        {ACTION_UPGRADE_MACHINE,  "up"}, //!< upgrade machine with up
        {ACTION_DESTROY_MACHINE,  "rm"}, //!< destroy machine with rm
}; //!< array of all the mappings

const UserActionMapping* mapping_getMapping( const char* seq )
{
    // check for all
    for ( int i = 0; i < USER_MAPPING_SIZE; i++ ) {
        if ( strcmp(seq, user_mapping[i].key) == 0 ) { //same
            // return mapping
            return &(user_mapping[i]);
        }
    }
    return NULL;
}

const UserActionMapping* mapping_getMappingByAction( Action action )
{
    // check for all
    for ( int i = 0; i < USER_MAPPING_SIZE; i++ ) {
        if ( user_mapping[i].actionID == action ) { //same
            // return mapping
            return &(user_mapping[i]);
        }
    }
    return NULL;
}

int mapping_getSize()
{
    return USER_MAPPING_SIZE;
}

const UserActionMapping* mapping_get( int index )
{
    // if in
    if ( index >= 0 && index < mapping_getSize() ) {
        return &(user_mapping[index]);
    }
    return NULL;
}

const UserActionMapping* mapping_getBackMapping()
{
    return mapping_getMappingByAction(ACTION_CANCEL_ACTION);
}