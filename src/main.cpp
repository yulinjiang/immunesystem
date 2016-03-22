#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sched.h>
#include <sys/shm.h>

#include "../include/popInit.h"
#include "../include/individuals.h"
#include "../include/fitness.h"
#include "../include/concentration.h"
#include "../include/excellence.h"
#include "../include/printData.h"
#include "../include/select.h"
#include "../include/bestSelect.h"
#include "../include/cross.h"
#include "../include/mutation.h"


void immuneProcess( struct individuals& newIndividuals, struct individuals* shareIndividual, int process)
{
		popInit( newIndividuals );
		printData( newIndividuals, ALL, "After popInit", process );

		for( int j = 1; j <= maxGen; j++ )
		{
				for( int chrom=1; chrom<=M ; chrom++)
				{
						newIndividuals.fitness[chrom] = fitness( newIndividuals, chrom);//更改适应度函数
						newIndividuals.concentration[ chrom ] = concentration( newIndividuals, chrom );
				}

				excellence( newIndividuals );
				bestSelect( newIndividuals );
				select( newIndividuals );
				cross( newIndividuals );
				mutation( newIndividuals );

				if( newIndividuals.fitness[ sizePop - overBest + 1 ] >= shareIndividual->fitness[ 31 ] )
				{
						for( int k = 1; k <= length; k++ )
								newIndividuals.chrom[ sizePop - overBest + 1 ][ k ] = shareIndividual->chrom[ 31 ][ k ];
				}
				else
				{
						for( int k = 1; k <= length; k++ )
								shareIndividual->chrom[ 31 ][ k ] = newIndividuals.chrom[ sizePop - overBest + 1 ][ k ];
						shareIndividual->fitness[ 31 ] = newIndividuals.fitness[ sizePop - overBest + 1 ];
				}

				printData( newIndividuals, ALL, "After mutation", process );
		}
}

int main( int argc, char* argv[])
{
		// printf("program begin!\n");
		//bind cpu
		cpu_set_t mask;
		CPU_ZERO( &mask );

		//fork
		pid_t woker;

		//create share memory
		// printf("create share memory begin!\n");
		void* shareMemory = ( void* )0;
		struct individuals* shareIndividual;
		int shmID = shmget( (key_t)1234, sizeof( struct individuals ), 0666 | IPC_CREAT );
		if( shmID == -1 )
				return 0;
		shareMemory = shmat( shmID, ( void* )0, 0 );
		if( shareMemory == ( void* )-1 )
				return 0;
		shareIndividual = ( struct individuals* )shareMemory;
		shareIndividual->fitness[ 31 ] = 999999;//only use 1 chrom

		//cul run time
		time_t tStart, tEnd;
		tStart = time( NULL );
		// printf("main process begin!\n");

		//program begin!
		for( int i = 1; i <= 4; i++ )
		{
				woker = fork();
				sleep( 1 );

				if( woker == 0 )
				{
						//bind cpu
						CPU_SET( i - 1, &mask );
						if( sched_setaffinity( 0, sizeof( mask ), &mask ) < 0 )
								printf( "sched_setaffinity fail\n" );

						/* printf( "Process %d is running!\n", i ); */

						srand( ( int ) time( NULL ) );                                                                                
						struct individuals newIndividuals;

						//main process
						immuneProcess( newIndividuals, shareIndividual, i );
						printData( *shareIndividual, ALL, "share memory", 0 );
						
						if( i == 4 )
						{
								printf( "%.20f\n", shareIndividual->fitness[ 31 ] );
								tEnd = time( NULL );
								// printf( "Run Time is %d\n", tEnd - tStart );
						}
						return 0;
				}
		}
		return 0;
}
