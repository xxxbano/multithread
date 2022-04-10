################################################################################
##
## Filename: 	Makefile
##
## Project: multithread samples	
##
## Creator:	Zhengfan Xia
##
################################################################################

#CFLAGS = -std=c++11 -pthread
CFLAGS = -pthread

SOURCES = $(wildcard *.c)
TARGET = $(patsubst %.c, %, $(SOURCES))

all: $(TARGET)

#$(TARGET): $(SOURCES) 
#	g++ $(CFLAGS) -o $@ $<

multithread: multithread.c

mutex: mutex.c

condition: condition.c

process: process.c

semaphore: semaphore.c

.PHONY: clean
clean:
	rm -rf $(TARGET)
