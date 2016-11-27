#Build rules
CC = gcc
CFLAGS = -g -Wall -std=c99 -D_GNU_SOURCE
LDLIBS = -lm

#Build planner, schedule, and activity
all: planner

planner: planner.o schedule.o activity.o

#Dependencies
planner: activity.h schedule.h
schedule: activity.h

# Clean files
clean:
	rm -f planner planner.o
	rm -f schedule schedule.o
	rm -f activity activity.o
