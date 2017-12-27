.PHONY: default help object executable all clean
CC = gcc

LD = $(CC)

VPATH = src/include:src
OUTDIR = bin
SOURCE_C = $(wildcard src/*.c) $(wildcard src/include/*.c)
OBJECTS_C = $(patsubst %.c, $(OUTDIR)/%_c.o, $(notdir $(SOURCE_C)))
CFLAGS = -std=gnu99 -O3 -Wall
EXECUTABLE = $(OUTDIR)/axelrod.e

default: help

help:
	@echo "\
Options:\n\n\
  make objects:       compiler makes objects for every *.c\n\
  make executable:    compiler makes executable\n\
  make all:           build all previous\n\
  make clean:         delete output files\n\
  make help:          display this help"

objects: $(OBJECTS_C)

executable: $(EXECUTABLE)

all: objects executable

print-%  : ; @echo $* = $($*)

$(OUTDIR)/%_c.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -lm

$(OUTDIR)/%.e: $(OBJECTS_C)
	$(LD) $(CFLAGS) $^ -o $@ -lm

clean:
	rm -rfv $(OBJECTS_C) $(EXECUTABLE) 
