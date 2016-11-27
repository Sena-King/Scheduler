/**
  @file activity.h

  Defines functions and a typedef for activity.c
*/

/** The Activity struct, which represents an activity. */
typedef struct Activity {
  /** The title of the activity. */
  char *title;
  /** Start hour */
  unsigned short shour;
  /** Start minute */
  unsigned short sminute;
  /** End hour */
  unsigned short ehour;
  /** End minute */
  unsigned short eminute;
  /** The month. */
  unsigned short month;
  /** The date. */
  unsigned short date;
} Activity;

/**
  Reads input from the file, and if the input is valid,
  dynamically allocates and initializes an instance of the Activity
  structure and returns a pointer to it. Returns NULL on failure.

  @param fp the input filestream
  @return the Activity Pointer
*/
Activity *readActivity( FILE *fp );

/**
  Frees the Activity at the input pointer.

  @param act the Activity pointer
*/
void freeActivity( Activity *act );
