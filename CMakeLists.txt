cmake_minimum_required(VERSION 3.10.2)

project(prim C)

set(CMAKE_C_STANDARD 99)

#########
# SETUP
#########

# cunit loader

FIND_PATH(CUNIT_INCLUDE_DIR NAMES CUnit/CUnit.h)
MARK_AS_ADVANCED(CUNIT_INCLUDE_DIR)
FIND_LIBRARY(CUNIT_LIBRARY NAMES
        cunit
        libcunit
        cunitlib
        )
MARK_AS_ADVANCED(CUNIT_LIBRARY)
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CUnit DEFAULT_MSG CUNIT_LIBRARY CUNIT_INCLUDE_DIR)

IF(CUNIT_FOUND)
    SET(CUNIT_LIBRARIES ${CUNIT_LIBRARY})
    SET(CUNIT_INCLUDE_DIRS ${CUNIT_INCLUDE_DIR})
ENDIF(CUNIT_FOUND)

###########
# Project
###########

# add_executable(prim run_suite_tests.c __old/tests/suite1.h __old/tests/suite1.c __old/tests/tests_utils.c __old/tests/tests_utils.h)
# add_executable(prim run_suite_tests.c tests/suite1.h tests/suite1.c tests/tests_utils.c tests/tests_utils.h)
# target_link_libraries(prim cunit ${CUNIT_LIBRARIES})

add_executable(main
        src/main.c
        src/model/map.c
        src/view/interface.c

        headers/map.h
        headers/interface.h

        headers/data/actions.h
        headers/data/difficulty.h
        headers/data/effect.h
        headers/data/machine.h
        headers/data/machine_info.h
        headers/data/staff.h
        headers/data/mapping.h
        headers/data/case_type.h
        headers/data/error.h
        headers/utils/structures.h

        headers/utils/utils.h

        src/main.h

        src/view/translation.c
        src/view/translation.h

        headers/utils/map_utils.h

        src/view/ncurses/interface_ncurses.c
        src/view/ncurses/interface_ncurses.h
        src/view/ncurses/interface_ncurses_utils.c
        src/view/ncurses/interface_ncurses_utils.h

        src/view/ncurses/modules/action.c
        src/view/ncurses/modules/difficulty.c
        src/view/ncurses/modules/location.c
        src/view/ncurses/modules/show.c
        src/view/ncurses/modules/staff.c
        src/utils/utils_fun.c src/utils/utils_fun.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c99")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c99")

SET(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries( main ${CURSES_LIBRARIES} )