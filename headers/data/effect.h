/*!
 * \file effect.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/03/2021
 * \see staff.h
 *
 * Contains information about effects
 */
#ifndef PRIM_EFFECT_H
#define PRIM_EFFECT_H

    #include <stdbool.h> // bool type
    #include "machine.h" // main information about a machine

    /*!
     * \typedef Target
     * \union Target_S effect.h "headers/data/effect.h"
     * \brief represent the target on which we will apply an effect
     */
    typedef union Target_S {
        MachineStuff machine; //!< machine related effects
        /*!
         * \typedef other
         * \enum SubTargets_S
         * \brief represent all targets that are not a machine
         */
        enum SubTargets_S {
            NONE, //!< nothing
            SUB_HIRE, //!< if we want to apply something to all hire related functions
            SUB_FISE, //!< if we want to apply something to hire fise related
            SUB_FISA, //!< if we want to apply something to hire fisa related
            DESTROY_GARBAGE //!< if we want to check destroy related effects
        } other; //!< represent all targets that are not a machine
    } Target; //!< target of the effect


    /*!
     * \typedef Mode
     * \enum Mode_S effect.h "headers/data/effect.h"
     * \brief mode activate when we do an action
     *
     * Different Action
     *
     */
    typedef enum Mode_S {
        CONSTRUCTION = 0, //!< create something, machine target
        UPGRADE = 1, //!< upgrade something, machine target
        DESTROY = 2,  //!< destroy something, machine target
        HIRE = 3, //!< hire someone, called when hiring, check other
        ON_BUY = 4, //!< called when staff bought
        SEND_DOOR = 5, //!< called when garbage are sent to the door
        DOOR_OUT = 6, //!< called when garbage are leaving the door
        PRODUCTION = 7, //!< called when we will create something (E, DD, ...)
        ON_TURN = 8 //!< apply each turn
    } Mode; //!< what do we do in our effect

    /*!
     * \typedef Effect
     * \struct Effect_S Staff.h "headers/data/Staff.h"
     *
     * Struct which contains the target of the effect
     *
     */
    typedef struct Effect_S {
        Mode mode; //!< represent the mode applied to the machine
        Target what; //!< represent the target of the effect
        bool onOther; //!< to know if what is a machine or other
        float modifierRes; //!< if SEND_DOOR, resource put in multiply by this
        int modifierFISA; //!< update the number of FISA
        int modifierFISE; //!< update the number of FISE
        int modifierE; //!< update the E cost
        int modifierDD; //!< update the DD cost
        int modifierCapacity; //!< update the capacity of the machine
        int min_costE; //!< check after update of E with min_cost_E
        int min_costDD;//!< check after update of DD with min_cost_DD
        char* description; //!< describe the effect
    } Effect; //!< Struct which contains the target and the of the effect

    // TODO ANtoine Faire toute la doc

    Mode effect_getMode(const Effect *effect);

    Target effect_getWhat(const Effect *effect);

    bool effect_getOnOther(const Effect *effect);

    int effect_getModifierRes(const Effect *effect);

    int effect_getModifierFISA(const Effect *effect);

    int effect_getModifierFISE(const Effect *effect);

    int effect_getModifierE(const Effect *effect);

    int effect_getModifierDD(const Effect *effect);

    int effect_getModifierCapacity(const Effect *effect);

    int effect_getMinCostE(const Effect *effect);

    int effect_getMinCostDD(const Effect *effect);

    char* effect_getDescription(const Effect *effect);

#endif //PRIM_EFFECT_H
