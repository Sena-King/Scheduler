/**
  @file schedule.c

  Implementation for the Schedule and related functions.
*/
#include "schedule.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Schedule *createSchedule() {
  Schedule *sch = (Schedule *)malloc( sizeof( Schedule ) );
  sch->list = (Activity **)malloc( 0 );
  sch->size = 0;
  return sch;
}

void freeSchedule( Schedule *sched ) {
  //A holder for the list size
  size_t listsize = sched->size;
  for ( int i = 0; i < listsize; i++ ) {
    freeActivity( sched->list[ i ] );
  }
  free( sched->list );
  free( sched );
}

void addActivity( Schedule *sched, Activity *act ) {
  //The length of the list
  size_t slen = sched->size;
  
  sched->list = (Activity **)realloc( sched->list ,
                 sizeof( Activity * ) * ( 1 + sched->size ) );
  ( sched->list )[ sched->size ] = act;
  ( sched->size )++;
}


int compareActivity( const void *a, const void *b ) {
  Activity **tempa = ( Activity ** )a;
  Activity **tempb = ( Activity ** )b;
  unsigned int atemp = ( *tempa )->month * 100 * 100 * 100 +
                       ( *tempa )->date * 100 * 100 +
                       ( *tempa )->shour * 100 +
                       ( *tempa )->sminute;
  unsigned int btemp = ( *tempb )->month * 100 * 100 * 100 +
                       ( *tempb )->date * 100 * 100 +
                       ( *tempb )->shour * 100 +
                       ( *tempb )->sminute;
  if ( atemp > btemp ) {
    return 1;
  }
  else if ( atemp < btemp ) {
    return -1;
  }
  return strcmp( ( *tempa )->activity, ( *tempb )->activity ); 
}

void readSchedule( Schedule *sched ) {
  FILE *fp = fopen( "schedule.txt", "r" );
  Activity *tempact;
  while( ( tempact = readActivity( fp ) ) )
    addActivity( sched, tempact );
  fclose( fp );
}

void saveSchedule( Schedule *sched ) {
  FILE *fp = fopen( "schedule.txt", "w" );
  for( int i = 0; i < sched->size; i++ ) {
    //Check for null spaces
    if( sched->list[ i ] ) {
      printf( "Date %02u/%02u Starts %02u:%02u Ends %02u:%02u __ %s __\n",
            sched->list[ i ]->month,
            sched->list[ i ]->date,
            sched->list[ i ]->shour,
            sched->list[ i ]->sminute,
            sched->list[ i ]->ehour,
            sched->list[ i ]->eminute,
            sched->list[ i ]->title );
    }
  }
  fclose( fp );
}

void printSchedule( Schedule *sched, 
                    bool (*test)( Activity *, void *arg ), 
                    void *arg) {
  //The length of the schedule
  size_t slen = sched->size;
  //The leader with the longest name
  int longest = 0;
  qsort( sched->list, slen, sizeof( Activity * ), compareActivity );

  //Print the rows
  printf( "\n" );
  for( int i = 0; i < slen; i++ ) {
    if( test( ( sched->list )[ i ], arg ) ) {
      printf( "Date %02u/%02u Starts %02u:%02u Ends %02u:%02u __ %s __\n",
            sched->list[ i ]->month,
            sched->list[ i ]->date,
            sched->list[ i ]->shour,
            sched->list[ i ]->sminute,
            sched->list[ i ]->ehour,
            sched->list[ i ]->eminute,
            sched->list[ i ]->title );
    }
  }
}
