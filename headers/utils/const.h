/*!
 * \file const.h
 * \author Ramzy ZEBRIR
 * \version 0.1
 * \date 04/04/2021
 *
 * Contains all consts
 *
 */
#ifndef PRIM_CONST_H
#define PRIM_CONST_H

    // todo: rename and change value back to 100 (Quentin)
    #define NUMBER_DD_DEPART 5000 //!< number of DD at the start of the game
    #define NUMBER_E_DEPART 5000 //!< number of E at the start of the game
    #define PRODUCTION_FISA_E 4 //!< number of E produced by FISA
    #define PRODUCTION_FISA_DD 4 //!< number of DD produced by FISA
    #define PRODUCTION_FISE_E 1 //!< number of E produced by FISE
    #define PRODUCTION_FISE_DD 1 //!< number of DD produced by FISE
    #define NUMBER_FISE 5 //!< number of FISE at the start of the game
    #define NUMBER_FISA 5 //!< number of FISA at the start of the game
    #define COST_FISE_E 50 //!< cost in E of FISE
    #define COST_FISE_DD 20 //!< cost in DD of FISE
    #define COST_FISA_E 50 //!< cost in E of FISA
    #define COST_FISA_DD 20 //!< cost in DD of FISA
    #define NB_TURN_FISA 2 //!< number of turns before FISA Production 
    #define NB_TURN_PRODUCTION_SOURCE 10 //!< number of turns before Source Production 
    #define NB_RESOURCE_PRODUCT_BY_SOURCE 3  //!< number of resource produced by Source
    //todo: remove ?
    #define NUMBER_DIRECTION 4 //!< number of direction
    #define NUMBER_WASTE_TO_PRODUCT_RESOURCE 10 //!< number of waste to product a resource in a recycling center

#endif //PRIM_CONST_H