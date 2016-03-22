#include "../include/printData.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <string.h>

void LogDebug( FILE* pFile, const char* format, ... )
{
		static time_t tCurrent = time( 0 );
		static char logInfomation[ 64 ];
		strftime( logInfomation, sizeof( logInfomation ), "<%Y-%m-%d><%H:%M:%S>", localtime( &tCurrent) );

		va_list args;
		va_start( args, format );
		
		char ch;
		int val;
		char* str;
		
		//print Time
		fprintf( pFile, "%s ", logInfomation );

		//main print
		while( *format )
		{
				ch = *format;
				if( ch != '%' )
						fprintf( pFile, "%c", ch );
				else
				{
						switch( *++format )
						{
								case 'd':
										val = va_arg( args, int );
										fprintf( pFile, "%d", val );
										break;
								case 's':
										str = va_arg( args, char* );
										fprintf( pFile, "%s", str );
										break;
								default :
										break;
						}
				}
				++format;
		}
		va_end( args );
		fprintf( pFile, "\n" );
}


void printData( struct individuals& newIndividuals, int type, const char* message, int process )
{
		time_t tCurrent = 0;
		char tmpCurrentTime[ 128 ];
		char strProcess[ 128 ];

		strcpy( tmpCurrentTime, "" );
		strcpy( strProcess, "" );
		
		FILE* pFile;

		tCurrent = time( 0 );
		strftime( tmpCurrentTime, sizeof( tmpCurrentTime ), "../log/%Y%m%d%H.log", localtime( &tCurrent ) );

		if( process == 0 )
				pFile = fopen( tmpCurrentTime, "a+" );
		else
		{
				snprintf( strProcess, sizeof( strProcess ), "%d", process );
				strcat( tmpCurrentTime, strProcess );
				pFile = fopen( tmpCurrentTime, "a+" );
				LogDebug( pFile, "Process %d", process );
		}

		//all type
		if( type == ALL )
		{
				LogDebug( pFile, "Individuals now is list as follow!");
				LogDebug( pFile, "%s", message);

				for ( int i = 1; i<= M; i++ )
				// for ( int i = sizePop + 1; i<= M; i++ )
				{
						if( i == sizePop + 1 )
								fprintf( pFile, " ============= elite chrom =============\n" );

						for( int j = 1;j <= length; j++ )
						{
								fprintf( pFile, "%.10f\t\t",newIndividuals.chrom[ i ][ j ] );
						}
						fprintf( pFile,  "Fit:%.10f\t\tCon:%.10f\t\tExc:%.10f\n", newIndividuals.fitness[ i ], newIndividuals.concentration[ i ], newIndividuals.excellence[ i ] );
				}
				fprintf( pFile, "\n" );
		}


		// chrom
		if( type == CHROM )
		{
				printf("Individuals now is list as follow!\n");
				for ( int i = 1; i<= M; i++ )
				{
						for( int j = 1;j <= length; j++ )
						{
								printf( "%3.3f\t",newIndividuals.chrom[ i ][ j ] );
						}
						puts("");
				}
		}

		//fitness
		if( type == FITNESS )
		{
				printf("Fitness now is list as follow!\n");
				for( int i = 1; i <= M; i++ )
						printf("%3.3f\n", newIndividuals.fitness[ i ] );
		}

		//concentration
		if( type == CONCENTRATION )
		{
				printf( "Concentration now is list as follow!\n" );
				for( int i = 1; i <= M; i++ )
						printf( "%3.5f\n", newIndividuals.concentration[ i ] );
		}


		//excellence 
		if( type == EXCELLENCE )
		{
				printf( "Excellence now is list as follow!\n" );
				for( int i = 1; i <= M; i++ )
						printf( "%3.5f\n", newIndividuals.excellence[ i ] );

		}

		fclose( pFile );

}

