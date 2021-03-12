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

    #include "effect.h" //! effect.h : information about effect

    /*!
     * \typedef Staff
     * \struct Staff_S staff.h "headers/data/staff.h"
     *
     * Struct which contains the target of the effect
     *
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
                            .modifier_E = -10,
                            .modifier_DD = -1,
                            .min_cost_E = 10,
                            .min_cost_DD = 1,
                            .description = "Le coût de construction des collecteurs diminue de 10E et 1DD (minimum 10E\n"
                                           "et 1DD)."
                    },

            }}};

#endif //PRIM_STAFF_H