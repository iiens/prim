###############################
# Prim, environment line
# Project version 0.0.5
# Authors Quentin Ra, Antoine MAN, Ramzy ZEBRIR and Valentin DREANO
#
# This makefile can be used instead of our CMakeLists.
# Version 1.0.0, Usage :
# - `make` : creates project, put executable in ./bin/prim
# - `make all` : same as make
# - `make clean` : clean .o files
# - `make run` : run ./a.out
###############################

# 1. main goal
all: prim

# 2. init variables
# compiler
CC= gcc
# compilation flags
CFLAGS= -Wall -Wextra -std=c99 -lncurses -lform

# path
OUTPUT=./obj/
OUTPUT_V=$(OUTPUT)view/
OUTPUT_M=$(OUTPUT)model/
OUTPUT_U=$(OUTPUT)utils/
OUTPUT_V_N=$(OUTPUT_V)ncurses/
OUTPUT_V_N_M=$(OUTPUT_V_N)modules/
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
SOURCE_V_N_M=$(SOURCE_V_N)modules/

# all interface modules object files
# we got 6 target to do
INTERFACE_MODULES = $(OUTPUT_V_N_M)action.o $(OUTPUT_V_N_M)difficulty.o $(OUTPUT_V_N_M)location.o $(OUTPUT_V_N_M)machine.o \
	$(OUTPUT_V_N_M)show.o $(OUTPUT_V_N_M)staff.o

# all off our project files
# 2-3 : we got our interface and 2 ncurses related and translation and our modules of course. Also a translation file.
# 4 : there related to the map
# 5 : utils
O_FILES= $(OUTPUT)main.o \
	$(OUTPUT_V)interface.o $(OUTPUT_V)translation.o \
	$(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o $(INTERFACE_MODULES) \
	$(OUTPUT_M)map.o $(OUTPUT_M)map_utils.o \
	$(OUTPUT_U)utils_fun.o

# all off our header files included in interface.h for convenience sake
# data ( line 2 - 4 )
# utils ( line 5 )
INTERFACE_DEP= $(SOURCE_H)map.h \
	$(SOURCE_H_D)difficulty.h $(SOURCE_H_D)actions.h $(SOURCE_H_D)case_type.h $(SOURCE_H_D)effect.h \
	$(SOURCE_H_D)machine.h $(SOURCE_H_D)machine_info.h $(SOURCE_H_D)staff.h $(SOURCE_H_D)error.h \
	$(SOURCE_H_D)mapping.h \
	$(SOURCE_H_U)map_utils.h $(SOURCE_H_U)structures.h $(SOURCE_H_U)translation.h $(SOURCE_H_U)utils.h

# 3. Dependencies

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
$(OUTPUT_M)map.o: $(SOURCE_M)map.c $(SOURCE_H)map.h $(INTERFACE_DEP) $(OUTPUT_M)map_utils.o
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)map.o $(SOURCE_M)map.c

# interface_ncurses.o
# - interface_ncurses.c and .h
# - interface_ncurses_utils.c and interface_ncurses_utils.h
$(OUTPUT_V_N)interface_ncurses.o: $(SOURCE_V_N)interface_ncurses.c $(SOURCE_V_N)interface_ncurses.h \
 		$(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N)interface_ncurses.o $(SOURCE_V_N)interface_ncurses.c

# ncurses utils
$(OUTPUT_V_N)interface_ncurses_utils.o: $(SOURCE_V_N)interface_ncurses_utils.c $(SOURCE_V_N)interface_ncurses_utils.h
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

$(OUTPUT_V_N_M)staff.o: $(SOURCE_V_N_M)staff.c $(OUTPUT_V_N)interface_ncurses.o $(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N_M) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N_M)staff.o $(SOURCE_V_N_M)staff.c

# translation.o
# - translation.c and .h
# - actions.h
# - machine.h
# - error.h
$(OUTPUT_V)translation.o: $(SOURCE_V)translation.c $(SOURCE_H_U)translation.h $(SOURCE_H_D)error.h $(SOURCE_H_D)machine.h $(SOURCE_H_D)actions.h
	mkdir -p $(OUTPUT_V) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V)translation.o $(SOURCE_V)translation.c

# utils_fun.o
# - utils_fun.c and .h
$(OUTPUT_U)utils_fun.o: $(SOURCE_U)utils_fun.c $(SOURCE_U)utils_fun.h
	mkdir -p $(OUTPUT_U) && $(CC) $(CFLAGS) -c -o $(OUTPUT_U)utils_fun.o $(SOURCE_U)utils_fun.c

# map_utils.o
# - map_utils.c and .h
# - difficulty.h
$(OUTPUT_M)map_utils.o: $(SOURCE_M)map_utils.c $(SOURCE_H_U)map_utils.h $(SOURCE_H_D)difficulty.h
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)map_utils.o $(SOURCE_M)map_utils.c

prim: $(O_FILES)
	$(CC) $(CFLAGS) -o bin/prim $(O_FILES)

# compile before run
# then run
run: prim
	./bin/prim

# 4. helpers
clean :
	rm -f $(O_FILES) bin/prim 2> /dev/null

.PHONY : clean