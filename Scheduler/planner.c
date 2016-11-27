/**
  @file planner.c

  Accepts command line arguments to modify and examine a schedule of activities.
*/

#include "schedule.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
  Checks if the given string b is a substring of a, case insenstitive.

  @param a the larger string
  @param b the shorter string
  @return true if b is a substring of a
*/
bool substr( const char *a, char *b ) {
  char *tempa = ( char * )malloc( strlen( a ) * sizeof( char ) );
  strcpy( tempa, a );
  //Converts a to lower
  for( int i = 0; i < strlen( tempa ); i++ ) {
    tempa[ i ] = tolower( tempa[ i ] );
  }
  //Converts b to lower
  for( int i = 0; i < strlen( b ); i++ ) {
    b[ i ] = tolower( b[ i ] );
  }
  if ( strstr( tempa, b ) )
    return true;
  return false;
}

/**
  The test for the schedule command. Always returns true.

  @param a the pointer to the Activity
  @param arg the input argument
  @return true always
*/
bool testSchedule( Activity* a, void *arg ) {
  return true;
}

/**
  The test for the match command.

  @param a the pointer to the Activity
  @param arg the keyword
  @return true if the keyword matches the event
*/
bool testMatch( Activity* a, void *arg ) {
  //Casts the argument
  char *temp = ( char * )arg;
  bool out = substr( a->title, temp );
  return out;
}

/**
  Accepts command line arguments to modify and examine a schedule of activities.

  @return the program exit status
*/
int main() 
{
  //Allocates the schedule
  Schedule *master;
  master = createSchedule();
  readSchedule( master );
  //The command
  char argument[ THOUSAND ];
  //Intentional infinite loop
  while( true ) {
    printf( "> " );
    if ( scanf( "%s", argument ) != 1 ) {
      break;
    }
    if ( strcmp( argument, "quit" ) == 0 ) {
      saveSchedule( master );
      break;
    }
    else if ( strcmp( argument, "schedule" ) == 0 ) {
      printSchedule( master, testSchedule, NULL );
    }
    //Checks if there is a separating space
    else if( getchar() != ' ' ){
      printf( "Invalid command\n" );
    }
    else if ( strcmp( argument, "add" ) == 0 ) {
      //Allocates the activity
      Activity *atemp = readActivity();
      if ( atemp == NULL ) {
        printf( "Invalid command\n" );
      }
      else {
        if ( addActivity( master, atemp ) ) {
          //Do nothing
        }
        else {
          freeActivity( atemp );
          printf( "Schedule conflict\n" );
        }
      }
    }
    else if ( strcmp( argument, "match" ) == 0 ) {
      char temp[ LEADER_LENGTH ];
      char c;
      scanf( "%20s", temp );
      if ( ( c = getchar() ) != '\n' && c != EOF ) {
        clear();
        printf( "Invalid command\n" );
      }
      else {
        printSchedule( master, testMatch, temp );
      }
    }
    else if ( strcmp( argument, "remove" ) == 0 ) {
      //The id number
      unsigned int num;
      scanf( "%u", &num );
      num--;
      //The index to remove
      int index = -1;
      unsigned int len = master->size;
      for ( int i = 0; i < len; i++ ) {
        if ( master->list[ i ]->id == num ) {
          index = i;
        }
      }
      if ( num < 0 )
        index = -1;
      if ( index == -1 ) {
        clear();
        printf( "Invalid command\n" );
      }
      else {
        freeActivity( master->list[ index ] );
        for( int i = index; i < len - 1; i++ ) {
          master->list[ i ] = master->list[ i + 1 ];
        }
      }
      //Shrink the list
      master->list = realloc( master->list, 
                              sizeof( Activity * ) * ( len - 1 ) );
      ( master->size )--;
    }
    else {
      printf( "Invalid command\n" );
    }
  }
  return 0;
}
