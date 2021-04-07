cmake_minimum_required(VERSION 3.10.2)

project(prim C)

set(CMAKE_C_STANDARD 99)

#########
# SETUP
#########

# cunit loader

FIND_PATH(CUNIT_INCLUDE_DIR NAMES CUnit/CUnit.h)
MARK_AS_ADVANCED(CUNIT_INCLUDE_DIR)
FIND_LIBRARY(CUNIT_LIBRARY NAMES cunit libcunit cunitlib)
MARK_AS_ADVANCED(CUNIT_LIBRARY)
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CUnit DEFAULT_MSG CUNIT_LIBRARY CUNIT_INCLUDE_DIR)

IF(CUNIT_FOUND)
    SET(CUNIT_LIBRARIES ${CUNIT_LIBRARY})
    SET(CUNIT_INCLUDE_DIRS ${CUNIT_INCLUDE_DIR})
ENDIF(CUNIT_FOUND)

# ncurses

SET(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

###########
# Project
###########

add_executable(AllTests
        tests/AllTests.c
        tests/testMap.h
        tests/testMap.c
        tests/listSuite.h headers/data/box.h)
target_link_libraries(AllTests cunit ${CUNIT_LIBRARIES})

add_executable(main
        src/main.c
        src/model/map.c
        src/view/interface.c
        src/view/translation.c
        src/view/ncurses/interface_ncurses.c
        src/view/ncurses/interface_ncurses_utils.c
        src/view/ncurses/modules/action.c
        src/view/ncurses/modules/difficulty.c
        src/view/ncurses/modules/location.c
        src/view/ncurses/modules/show.c
        src/view/ncurses/modules/staff.c
        src/view/ncurses/modules/machine.c
        src/utils/utils_fun.c
        src/model/staff.c
        src/model/effect.c
        src/model/machine_info.c
        src/model/machine.c
        src/model/map_utils.c

        headers/utils/structures.h
        src/utils/structure.c src/model/case.c src/model/box.c)

target_include_directories(main PUBLIC /headers)
target_link_libraries( main ${CURSES_LIBRARIES} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c99")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c99")