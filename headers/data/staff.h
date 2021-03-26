/*!
 * \file staff.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/03/2021
 * \see effect.h
 *
 * Contains all information about the character of the Staff
 */
#ifndef PRIM_STAFF_H
#define PRIM_STAFF_H

    #include "effect.h" // effect.h : information about effect

    /*!
     * \typedef Staff
     * \struct Staff_S staff.h "headers/data/staff.h"
     * \brief Struct which contains the target of the effect
     */
    typedef struct Staff_S {
        int id; //!< id of the character
        char* name; //!< name of the character
        int costE; //!< Price in E of the character
        int costDD; //!< Price in DD of the character
        char* description; //!< description of character effects
        Effect effects[20]; //!< array which contains the target of the effect
    } Staff; //!< information about staff

const Staff staff_list[] = {
        {1, "Fetia Bannour", 100, 30, "The cost of constructing collectors"
                                      "decreases by 10EE and 1DD ", .effects = {
                {
                        .mode = CONSTRUCTION,
                        .onOther = false,
                        .what.machine = MS_COLLECTOR,
                        .modifierE = -10,
                        .modifierDD = -1,
                        .min_costE = 10,
                        .min_costDD = 1,
                        .description = "The cost of constructing collectors decreases by 10EE and 1DD (min 10EE\n"
                                       "and 1DD)."
                },

        }},
        {2, "Kevin Goilard", 100, 30, "The cost of constructing conveyor belt"
                                      "decreases by 3EE and 1DD ", .effects = {
                {
                        .mode = CONSTRUCTION,
                        .onOther = false,
                        .what.machine = MS_CONVEYOR_BELT,
                        .modifierE = -3,
                        .modifierDD = -1,
                        .min_costE = 3,
                        .min_costDD = 1,
                        .description = "The cost of constructing conveyor belt decreases by 3EE and 1DD (min 3EE\n"
                                       "and 1DD)."
                },

        }},
        {2, "Vincent Jeannas", 100, 30, "The cost of constructing cross"
                                        "decreases by 8EE and 1DD ", .effects = {
                {
                        .mode = CONSTRUCTION,
                        .onOther = false,
                        .what.machine = MS_CROSS,
                        .modifierE = -8,
                        .modifierDD = -1,
                        .min_costE = 8,
                        .min_costDD = 1,
                        .description = "The cost of constructing cross decreases by 8EE and 1DD (min 8EE\n"
                                       "and 1DD)."
                },

        }},
        {2, "Kevin Goilard", 100, 30, "The cost of constructing conveyor belt"
                                      "decreases by 3EE and 1DD ", .effects = {
                {
                        .mode = CONSTRUCTION,
                        .onOther = false,
                        .what.machine = MS_CONVEYOR_BELT,
                        .modifierE = -3,
                        .modifierDD = -1,
                        .min_costE = 3,
                        .min_costDD = 1,
                        .description = "The cost of constructing conveyor belt decreases by 3EE and 1DD (min 3EE\n"
                                       "and 1DD)."
                },

        }},














};


#endif //PRIM_STAFF_H