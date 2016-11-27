/**
  @file activity.c

  Implementation for an Activity and related functions.
*/
#include "activity.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Activity *readActivity( FILE *fp ) {
  //Assumes the leading space is removed
  //The pointer to the title
  char *titleholder = malloc( 0 );
  //The title length
  long ntitle = 0;
  //A char to hold user input.
  char temp;
  //The start hour/minute, end hour/minute, date/month
  unsigned short tshour, tsminute, tehour, teminute, tmonth, tdate;
  //Gets the time parameters.
  printf( "Enter the month.\n> " );
  if ( !fscanf( fp, "%hu", tmonth ) )
    return NULL;
  if( tmonth > 12 )
    return NULL;
  printf( "Enter the date.\n> " );
  if ( !fscanf( fp, "%hu", tdate ) )
    return NULL;
  if( tdate > 31 )//Add calendar checking later.
    return NULL;
  printf( "Enter the starting hour.\n> " );
  if ( !fscanf( fp, "%hu", tshour ) )
    return NULL;
  if( tshour > 23 )
    return NULL;
  printf( "Enter the starting minute.\n> " );
  if ( !fscanf( fp, "%hu", tsminute ) )
    return NULL;
  if( tsminute > 59 )
    return NULL;
  printf( "Enter the ending hour.\n> " );
  if ( !fscanf( fp, "%hu", tehour ) );
    return NULL;
  if( tehour > 23 )
    return NULL;
  printf( "Enter the ending minute.\n> " );
  if ( !fscanf( fp, "%hu", teminute ) )
    return NULL;
  if( teminute > 59 )
    return NULL;

  //Gets the activity name
  printf( "Enter the activity name.\n> " );
  while ( ( temp = fgetc( fp ) ) != '\n' && temp != EOF ) {
    ntitle++;
    titleholder = realloc(titleholder, ntitle * sizeof( char ) );
    titleholder[ ntitle - 1 ] = temp;
  }
  if ( ntitle == 0 ) {
    return NULL;
  }
  else {
    ntitle++;
    titleholder = realloc(titleholder, ntitle * sizeof( char ) ); 
    titleholder[ ntitle - 1 ] = '\0';
  }
  //Allocates the activity
  Activity *output = ( Activity * )malloc( sizeof( Activity ) );
  output->title = titleholder;
  output->shour = tshour;
  output->sminute = tsminute;
  output->ehour = tehour;
  output->eminute = teminute;
  output->month = tmonth;
  output->date = tdate;
  return output;
}

void freeActivity( Activity *act ) {
  free( act->title );
  free( act );
}
