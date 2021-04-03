#include "CUnit/Basic.h"
#include "CUnit/Console.h"
#include "CUnit/Automated.h"
#include "CUnit/CUCurses.h" /* only on systems having curses */

// Tests files
#include "listSuite.h"

int main()
{
    int res;
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    for (int i = 0; i < NUMBERSUITE; i++) {
        res = listSuit[i](pSuite);
        if (res == EXIT_FAILURE) {
            CU_cleanup_registry();
            return CU_get_error();
        }
    }

    /* Run all tests using the basic interface */
    /*CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");*/

    /* Run all tests using the automated interface */
    //CU_automated_run_tests();
    //CU_list_tests_to_file();

    /* Run all tests using the console interface */
    CU_console_run_tests();

    /* Run all tests using the curses interface */
    /* (only on systems having curses) */
    //CU_curses_run_tests();

    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
