# # # # # # #
# Makefile for project 1
#
# changed from Makefile made by Matt Farrugia
#

CC     = gcc
CFLAGS = -Wall -std=c99
EXE    = crack
OBJ    = crack.o sha256.o

# top (default) target
all: $(EXE)

# link executable
$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

# dependencies
crack.o: sha256.h

# phony targets
.PHONY: clean cleanly all CLEAN
# `make clean` to remove all object files
# `make CLEAN` to remove all object and executable files
# `make cleanly` to `make` then immediately remove object files
clean:
	rm -f $(OBJ)
CLEAN: clean
	rm -f $(EXE)
cleanly: all clean
