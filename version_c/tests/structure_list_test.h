/*!
 * \file structure_list_test.h
 * \author Valentin DREANO
 * \version 0.1
 * \date 17/04/2021
 *
 * Contains the structure to store the tests
 *
 */

#ifndef STRUCTURE_LIST_TEST_H
#define STRUCTURE_LIST_TEST_H

/*!
 * \typedef test_List
 * \struct test_List_S structure_list_test.h "tests/structure_list_test.h"
 * \brief Structure for storing the different test
 *
 * Structure for storing the different test
 */
struct test_List_S {
    char* description; //!< Allows you to write the test description
    void (*function)(void); //!< Store the function to be executed
}; //!< Stores information for a test

typedef struct test_List_S test_List; //!< Stores information for a test

#endif //STRUCTURE_LIST_TEST_H
