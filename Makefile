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
OUTPUT_V_N=$(OUTPUT_V)ncurses/
# src
SOURCE=./src/
SOURCE_H=./headers/
SOURCE_V=$(SOURCE)view/
SOURCE_M=$(SOURCE)model/
SOURCE_V_N=$(SOURCE_V)ncurses/
# files (without .o)
O_FILES= $(OUTPUT)main.o $(OUTPUT_V)interface.o $(OUTPUT_V_N)interface_ncurses.o \
	$(OUTPUT_V_N)interface_ncurses_utils.o $(OUTPUT_M)map.o

INTERFACE_DEP=headers/map.h \
	headers/data/difficulty.h headers/data/actions.h \
	headers/data/case_type.h headers/data/effect.h \
	headers/data/machine.h headers/data/machine_info.h \
	headers/data/staff.h headers/data/error.h \
	headers/data/mapping.h headers/utils/utils.h

# 3. Dependencies

# main.o
$(OUTPUT)main.o: $(SOURCE)main.c $(SOURCE_H)interface.h $(INTERFACE_DEP)
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
$(OUTPUT_M)map.o: $(SOURCE_M)map.c $(SOURCE_H)map.h $(INTERFACE_DEP)
	mkdir -p $(OUTPUT_M) && $(CC) $(CFLAGS) -c -o $(OUTPUT_M)map.o $(SOURCE_M)map.c

# interface_ncurses.o
# - interface_ncurses.c and .h
# - interface_ncurses_utils.c and interface_ncurses_utils.h
$(OUTPUT_V_N)interface_ncurses.o: $(SOURCE_V_N)interface_ncurses.c $(SOURCE_V_N)interface_ncurses.h \
 		$(OUTPUT_V_N)interface_ncurses_utils.o
	mkdir -p $(OUTPUT_V_N) && $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N)interface_ncurses.o $(SOURCE_V_N)interface_ncurses.c

$(OUTPUT_V_N)interface_ncurses_utils.o: $(SOURCE_V_N)interface_ncurses_utils.c $(SOURCE_V_N)interface_ncurses_utils.h
	mkdir -p $(OUTPUT_V_N) &&  $(CC) $(CFLAGS) -c -o $(OUTPUT_V_N)interface_ncurses_utils.o $(SOURCE_V_N)interface_ncurses_utils.c

prim: $(O_FILES)
	$(CC) $(CFLAGS) -o bin/prim $(O_FILES)

# 4. helpers
clean :
	rm -f $(O_FILES) bin/prim 2> /dev/null

.PHONY : clean