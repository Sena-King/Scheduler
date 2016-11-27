/**
  @file schedule.h

  Defines functions and a typedef for schedule.c
*/

#include "activity.h"
#include <stdbool.h>

/** The Schedule struct, which represents a schedule. */
typedef struct Schedule {
  /** The resizable list of activity pointers */
  Activity **list;
  /** The size of the array */
  unsigned int size;
} Schedule;

/**
  Dynamically allocates memory for a Schedule, and returns
  its pointer.

  @return the Schedule pointer
*/
Schedule *createSchedule();

/**
  Frees a Schedule at the input parameter.

  @param sched the Schedule pointer.
*/
void freeSchedule( Schedule *sched );

/**
  Adds an activity to the list.

  @param sched the schedule pointer
  @param act the activity pointer
*/
void addActivity( Schedule *sched, Activity *act );

/**
  Compares two activities, returns negative if the starting time of a < b, 
  positive if the starting time of a > b.

  @param a the pointer to activity a
  @param b the pointer to activity b
  @return the comparison result
*/
int compareActivity( const void *a, const void *b );

/**
  Reads the schedule from the schedule.txt file.

  @param sched the schedule to read
*/
void readSchedule( Schedule *sched );


/**
  Saves the schedule to the schedule.txt file.

  @param sched the schedule to save
*/
void saveSchedule( Schedule *sched );

/**
  Saves the schedule to the schedule.txt file.

  @param sched the schedule to print
*/
void printSchedule( Schedule *sched );

/**
  Prints the schedule, filtered by the test function and the argument parameter.

  @param sched the schedule pointer
  @param test the test function
  @param arg the test function argument
*/
void printSchedule( Schedule *sched, 
                    bool (*test)( Activity *, void *arg ), 
                    void *arg);


