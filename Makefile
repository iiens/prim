###############################
# Prim, environment line
# Project version 0.0.5
# Authors Quentin Ra, Antoine MAN, Ramzy ZEBRIR and Valentin DREANO
#
# This makefile can be used instead of our CMakeLists.
# Version 1.2.1, Usage :
# - `make` : creates project, put executable in ./bin/prim
# - `make all` : same as make
# - `make prim` : same as make
# - `make tests` : make all tests, put executable in ./bin/tests
# - `make clean` : clean .o files
# - `make run` : run ./a.out
###############################

# 1. main goal
all: prim

# 2. init variables
# compiler
CC= gcc
# compilation flags
# https://stackoverflow.com/questions/154630/recommended-gcc-warning-options-for-c
CFLAGS= -Wall -Wextra -std=c99 -g
C_TESTS_FLAGS=$(CFLAGS)
# -m64 -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes
NCURSES_FLAGS=-D_DEFAULT_SOURCE -D_XOPEN_SOURCE=700 -lncursesw -lform
CUNIT_FLAGS=-lcunit

# path
OUTPUT=./obj/
OUTPUT_V=$(OUTPUT)view/
OUTPUT_M=$(OUTPUT)model/
OUTPUT_T=$(OUTPUT)tests/
OUTPUT_U=$(OUTPUT)utils/
OUTPUT_V_N=$(OUTPUT_V)ncurses/
OUTPUT_V_N_M=$(OUTPUT_V_N)modules/
OUTPUT_V_N_H=$(OUTPUT_V_N)headers/
# src
SOURCE=./src/
SOURCE_H=./headers/
SOURCE_H_D=$(SOURCE_H)data/
SOURCE_H_U=$(SOURCE_H)utils/
SOURCE_V=$(SOURCE)view/
SOURCE_M=$(SOURCE)model/
SOURCE_U=$(SOURCE)utils/
SOURCE_V_N=$(SOURCE_V)ncurses/
# ncurses module
SOURCE_V_N_H=$(SOURCE_V_N)nc_headers/
SOURCE_V_N_M=$(SOURCE_V_N)modules/
SOURCE_T=tests/

########################
######### DEPENDENCIES
########################

# all interface modules object files
# we got 7 target to do
INTERFACE_MODULES = $(OUTPUT_V_N_M)action.o $(OUTPUT_V_N_M)difficulty.o $(OUTPUT_V_N_M)location.o \
 	$(OUTPUT_V_N_M)machine.o $(OUTPUT_V_N_M)show.o $(OUTPUT_V_N_M)staff.o $(OUTPUT_V_N_M)game.o

# map
BASIC_FILES= $(OUTPUT_M)map.o $(OUTPUT_M)map_utils.o $(OUTPUT_M)staff.o $(OUTPUT_M)effect.o \
	$(OUTPUT_M)machine.o $(OUTPUT_M)machine_info.o $(OUTPUT_M)case.o $(OUTPUT_M)box.o $(OUTPUT_M)facade.o \
	$(OUTPUT_U)utils_fun.o $(OUTPUT_U)structures.o $(OUTPUT_U)elements.o $(OUTPUT_M)difficulty.o

# all off our project files
O_FILES= $(OUTPUT)main.o \
	$(OUTPUT_V)interface.o $(OUTPUT_V)translation.o $(OUTPUT_V)mapping.o \
	$(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o $(INTERFACE_MODULES) \
	$(BASIC_FILES)

# tests files
# all normal files
# and all tests files
O_TESTS_FILES= $(OUTPUT_T)tests.o $(BASIC_FILES) \
	$(OUTPUT_T)test_case.o $(OUTPUT_T)test_machine.o $(OUTPUT_T)test_map.o \
	$(OUTPUT_T)test_structure.o $(OUTPUT_T)test_box.o $(OUTPUT_T)test_endTurn.o

# all off our header files included in interface.h for convenience sake
# data ( line 2 - 4 )
# utils ( line 5 )
INTERFACE_DEP= $(SOURCE_H)map.h \
	$(SOURCE_H_D)difficulty.h $(SOURCE_H_D)actions.h $(SOURCE_H_D)case.h $(SOURCE_H_D)effect.h \
	$(SOURCE_H_D)machine.h $(SOURCE_H_D)machine_info.h $(SOURCE_H_D)staff.h $(SOURCE_H_D)error.h \
	$(SOURCE_H_D)mapping.h $(SOURCE_H_D)box.h \
	$(SOURCE_H_U)const.h $(SOURCE_H_U)map_utils.h $(SOURCE_H_U)structures.h $(SOURCE_H_U)elements.h  \
	$(SOURCE_H_U)translation.h $(SOURCE_H_U)utils.h

##################
# 3. Dependencies
##################

# main.o
$(OUTPUT)main.o: $(SOURCE)main.c $(SOURCE)main.h $(SOURCE_H)interface.h $(INTERFACE_DEP)
	mkdir -p $(OUTPUT) && $(CC) $(CFLAGS) -c -o $(OUTPUT)main.o $(SOURCE)main.c

# interface.o
# - interface.c and .h
# - all interface.h deps
# - interface_ncurses.c and interface_ncurses.h
$(OUTPUT_V)interface.o: $(SOURCE_V)interface.c $(SOURCE_H)interface.h $(INTERFACE_DEP) $(OUTPUT_V_N)interface_ncurses.o
	mkdir -p $(OUTPUT_V) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V)interface.o $(SOURCE_V)interface.c

# map.o
# - map.c and .h
# - all interface.h (~map.h) deps
# - map_utils.c and map_utils.h
$(OUTPUT_M)map.o: $(SOURCE_M)map.c $(SOURCE_H)map.h $(INTERFACE_DEP) $(OUTPUT_M)map_utils.o $(OUTPUT_M)machine.o \
 	$(OUTPUT_M)machine_info.o $(OUTPUT_M)effect.o
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)map.o $(SOURCE_M)map.c

# interface_ncurses.o
# - interface_ncurses.c and .h
# - interface_ncurses_utils.c and interface_ncurses_utils.h
$(OUTPUT_V_N)interface_ncurses.o: $(SOURCE_V_N)interface_ncurses.c $(SOURCE_V_N_H)interface_ncurses.h \
 		$(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N)interface_ncurses.o $(SOURCE_V_N)interface_ncurses.c

# ncurses utils
$(OUTPUT_V_N)interface_ncurses_utils.o: $(SOURCE_V_N)interface_ncurses_utils.c $(SOURCE_V_N_H)interface_ncurses_utils.h \
	$(SOURCE_V_N_H)interface_ncurses_constants.h
	mkdir -p $(OUTPUT_V_N) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N)interface_ncurses_utils.o $(SOURCE_V_N)interface_ncurses_utils.c

# ncurses modules
$(OUTPUT_V_N_M)action.o: $(SOURCE_V_N_M)action.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)action.o $(SOURCE_V_N_M)action.c

$(OUTPUT_V_N_M)difficulty.o: $(SOURCE_V_N_M)difficulty.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)difficulty.o $(SOURCE_V_N_M)difficulty.c

$(OUTPUT_V_N_M)location.o: $(SOURCE_V_N_M)location.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)location.o $(SOURCE_V_N_M)location.c

$(OUTPUT_V_N_M)machine.o: $(SOURCE_V_N_M)machine.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)machine.o $(SOURCE_V_N_M)machine.c

$(OUTPUT_V_N_M)show.o: $(SOURCE_V_N_M)show.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)show.o $(SOURCE_V_N_M)show.c

$(OUTPUT_V_N_M)game.o: $(SOURCE_V_N_M)game.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)game.o $(SOURCE_V_N_M)game.c

$(OUTPUT_V_N_M)staff.o: $(SOURCE_V_N_M)staff.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o $(OUTPUT_M)staff.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)staff.o $(SOURCE_V_N_M)staff.c

# translation.o
# - translation.c and .h
# - actions.h
# - machine.h
# - error.h
$(OUTPUT_V)translation.o: $(SOURCE_V)translation.c $(SOURCE_H_U)translation.h \
	$(SOURCE_H_D)error.h $(SOURCE_H_D)machine.h $(SOURCE_H_D)actions.h $(SOURCE_H_D)case.h
	mkdir -p $(OUTPUT_V) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V)translation.o $(SOURCE_V)translation.c

# translation.o
# - translation.c and .h
# - actions.h
# - machine.h
# - error.h
$(OUTPUT_V)mapping.o: $(SOURCE_V)mapping.c $(SOURCE_H_D)mapping.h
	mkdir -p $(OUTPUT_V) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V)mapping.o $(SOURCE_V)mapping.c

# utils_fun.o
# - utils_fun.c and .h
$(OUTPUT_U)utils_fun.o: $(SOURCE_U)utils_fun.c $(SOURCE_H_U)utils_fun.h
	mkdir -p $(OUTPUT_U) && $(CC) $(CFLAGS) -c -o $(OUTPUT_U)utils_fun.o $(SOURCE_U)utils_fun.c

# structures.o
# - structures.c and .h
$(OUTPUT_U)structures.o: $(SOURCE_U)structures.c $(SOURCE_H_U)structures.h
	mkdir -p $(OUTPUT_U) && $(CC) $(CFLAGS) -c -o $(OUTPUT_U)structures.o $(SOURCE_U)structures.c

# elements.o
# - structures.c and .h
$(OUTPUT_U)elements.o: $(SOURCE_U)elements.c $(SOURCE_H_U)elements.h
	mkdir -p $(OUTPUT_U) && $(CC) $(CFLAGS) -c -o $(OUTPUT_U)elements.o $(SOURCE_U)elements.c

# map_utils.o
# - map_utils.c and .h
# - difficulty.h
$(OUTPUT_M)map_utils.o: $(SOURCE_M)map_utils.c $(SOURCE_H_U)map_utils.h $(SOURCE_H_D)difficulty.h $(OUTPUT_M)effect.o
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)map_utils.o $(SOURCE_M)map_utils.c

# staff.o
# - staff.c and .h
$(OUTPUT_M)staff.o: $(SOURCE_M)staff.c $(SOURCE_H_D)staff.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)staff.o $(SOURCE_M)staff.c

# effect.o
# - effect.c and .h
$(OUTPUT_M)effect.o: $(SOURCE_M)effect.c $(SOURCE_H_D)effect.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)effect.o $(SOURCE_M)effect.c

# difficulty.o
# - difficulty.c and .h
$(OUTPUT_M)difficulty.o: $(SOURCE_M)difficulty.c $(SOURCE_H_D)difficulty.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)difficulty.o $(SOURCE_M)difficulty.c

# facade.o
# - facade.c and .h
$(OUTPUT_M)facade.o: $(SOURCE_M)facade.c $(SOURCE_H_D)facade.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)facade.o $(SOURCE_M)facade.c

# box.o
# - box.c and .h
$(OUTPUT_M)box.o: $(SOURCE_M)box.c $(SOURCE_H_D)box.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)box.o $(SOURCE_M)box.c

# case.o
# - case.c and .h
$(OUTPUT_M)case.o: $(SOURCE_M)case.c $(SOURCE_H_D)case.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)case.o $(SOURCE_M)case.c

# machine_info.o
# - machine_info.c and .h
$(OUTPUT_M)machine_info.o: $(SOURCE_M)machine_info.c $(SOURCE_H_D)machine_info.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)machine_info.o $(SOURCE_M)machine_info.c

# machine_info.o
# - machine_info.c and .h
$(OUTPUT_M)machine.o: $(SOURCE_M)machine.c $(SOURCE_H_D)machine.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)machine.o $(SOURCE_M)machine.c

#################################
######### DEPENDENCIES (tests)
################################

$(OUTPUT_T)tests.o: $(SOURCE_T)tests.c  $(SOURCE_T)list_suite.h $(SOURCE_T)structure_list_test.h \
		$(SOURCE)main.h $(SOURCE_H)interface.h $(INTERFACE_DEP)
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)tests.o $(SOURCE_T)tests.c

$(OUTPUT_T)test_case.o: $(SOURCE_T)test_case.c $(SOURCE_T)test_case.h
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)test_case.o $(SOURCE_T)test_case.c

$(OUTPUT_T)test_machine.o: $(SOURCE_T)test_machine.c $(SOURCE_T)test_machine.h
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)test_machine.o $(SOURCE_T)test_machine.c

$(OUTPUT_T)test_map.o: $(SOURCE_T)test_map.c $(SOURCE_T)test_map.h
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)test_map.o $(SOURCE_T)test_map.c

$(OUTPUT_T)test_structure.o: $(SOURCE_T)test_structure.c $(SOURCE_T)test_structure.h
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)test_structure.o $(SOURCE_T)test_structure.c

$(OUTPUT_T)test_box.o: $(SOURCE_T)test_box.c $(SOURCE_T)test_box.h
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)test_box.o $(SOURCE_T)test_box.c

$(OUTPUT_T)test_endTurn.o: $(SOURCE_T)test_endTurn.c $(SOURCE_T)test_endTurn.h
	mkdir -p $(OUTPUT_T) && $(CC) $(CFLAGS) -c -o $(OUTPUT_T)test_endTurn.o $(SOURCE_T)test_endTurn.c

####################
######### TASKS
####################

# Note: we don't put main inside our variable since having two main
# can mess up everything

prim: $(O_FILES)
	$(CC) $(CFLAGS) -o bin/prim $(O_FILES) $(NCURSES_FLAGS)

tests: $(O_TESTS_FILES)
	$(CC) $(C_TESTS_FLAGS) -o bin/tests $(O_TESTS_FILES) $(CUNIT_FLAGS) $(NCURSES_FLAGS)

# compile before run
# then run
run: prim
	./bin/prim

run_tests: tests
	./bin/tests

# 4. helpers
clean :
	rm -f $(O_FILES) bin/prim bin/tests 2> /dev/null

.PHONY : clean