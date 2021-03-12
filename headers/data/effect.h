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


    #include "machine.h" //!<

    /*!
    * \union Target_S effect.h "headers/data/effect.h"
    * \typedef Target
    * \brief represent the target , a machine or a staff
    *
    * Different Target
    *
    */
    typedef union Target_S {
        MachineStuff machine; //!< machine related effects
        enum SubTargets_S {
            NONE, //!< nothing
            SUB_HIRE, //!< if we want to apply something to all hire related functions
            SUB_FISE, //!< if we want to apply something to hire fise related
            SUB_FISA, //!< if we want to apply something to hire fisa related
            DESTROY_GARBAGE //!< if we want to check destroy related effects
        } other;
    } Target; //!< target of the effect


    /*!
    * \enum Mode_S effect.h "headers/data/effect.h"
    * \typedef Mode
    * \brief mode activate when we do an action
    *
    * Different Action
    *
    */
    typedef enum Mode_S {
        CONSTRUCTION = 0, //!< create something, machine target
        UPGRADE = 1, //!< upgrade something, machine target
        DESTROY = 2,  //!< destroy something, machine target
        HIRE  = 3, //!< hire someone, called when hiring, check other
        ON_BUY  = 4, //!< called when staff bought
        SEND_DOOR = 5, //!< called when garbage are sent to the door
        DOOR_OUT  = 6, //!< called when garbage are leaving the door
        PRODUCTION  = 7, //!< called when we will create something (E, DD, ...)
        ON_TURN  = 8 //!< apply each turn
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
        bool onOther; //!< todo :
        int modifier_res; //!< if SEND_DOOR, resource put in multiply by this
        int modifier_FISA; //!< update the number of FISA
        int modifier_FISE; //!< update the number of FISE
        int modifier_E; //!< update the E cost
        int modifier_DD; //!< update the DD cost
        int min_cost_E; //!< check after update of E with min_cost_E
        int min_cost_DD;//!< check after update of DD with min_cost_DD
        char * description; //!< describe the effect
    } Effect; //!< Struct which contains the target and the of the effect

#endif //PRIM_EFFECT_H
