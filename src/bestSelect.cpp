#include "../include/bestSelect.h"
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

struct sortFitness
{
		int index;
		double fitness;
}; 

struct sortExcellence
{
		int index;
		double excellence;
}; 

bool cmpFitness( struct sortFitness A, struct sortFitness B )
{
		return A.fitness < B.fitness;
}

bool cmpExcellence( struct sortExcellence A, struct sortExcellence B )
{
		return A.excellence > B.excellence;
}

void printNewInd( struct individuals& newIndividuals, const char* message )
{
		printf("NewIndividuals now is list as follow!\n");
		printf("%s\n", message );
		for ( int i = 1; i<= M; i++ )
		{
				if( i == sizePop + 1 )
						puts(" ============= elite chrom =============" );
				
				printf("The[ %d ]\t", i);

				for( int j = 1;j <= length; j++ )
				{
						printf( "%3.3f\t",newIndividuals.chrom[ i ][ j ] );
				}
				printf( "Fitness:%f\tConcentration:%f\tExcellence:%f", newIndividuals.fitness[ i ], newIndividuals.concentration[ i ], newIndividuals.excellence[ i ] );
				puts("");
		}
		puts("\n");
}

void bestSelect( struct individuals& oldIndividuals )
{
		struct individuals newIndividuals;	

		sortFitness myFitness[ M + 1 ];
		int oldFitnessPosition[ M + 1 ];

		sortExcellence myExcellence[ M + 1 ];
		int oldExcellencePosition[ M + 1 ];

		const int superChrom = 3;

		//Before sort!
		for( int i = 1;  i <= M; i++ )
		{
				myFitness[ i ].index = i;
				myFitness[ i ].fitness = oldIndividuals.fitness[ i ];

				myExcellence[ i ].index = i;
				myExcellence[ i ].excellence = oldIndividuals.excellence[ i ];
		}

		//sort Fitness
		sort( myFitness + 1, myFitness + M + 1, cmpFitness );
		for( int i = 1; i <= M; i++)
				oldFitnessPosition[ i ] = myFitness[ i ].index;

		//update newIndividuals by fitness ==================================
		//
		for( int i = 1; i <= superChrom; i++ )
		{
				newIndividuals.fitness[ i ] = oldIndividuals.fitness[ oldFitnessPosition[ i ] ];
				newIndividuals.excellence[ i ] = oldIndividuals.excellence[ oldFitnessPosition[ i ] ];
				newIndividuals.concentration[ i ] = oldIndividuals.concentration[ oldFitnessPosition[ i ] ];
				for( int j = 1; j <= length; j++ )
						newIndividuals.chrom[ i ][ j ] = oldIndividuals.chrom[ oldFitnessPosition[ i ] ][ j ];

				//get rid of selected chrom
				myExcellence[ oldFitnessPosition[ i ] ].excellence = -9999.0;
		}


		//  1
		//  =======================
		sort( myExcellence + 1, myExcellence + M + 1, cmpExcellence );
		for( int i = 1; i <= M; i++)
				oldExcellencePosition[ i ] = myExcellence[ i ].index;


		//update newIndividuals by excellence
		for( int i = superChrom + 1; i <= M; i++ )
		{
				newIndividuals.fitness[ i ] = oldIndividuals.fitness[ oldExcellencePosition[ i - superChrom ] ];
				newIndividuals.excellence[ i ] = oldIndividuals.excellence[ oldExcellencePosition[ i - superChrom ] ];
				newIndividuals.concentration[ i ] = oldIndividuals.concentration[ oldExcellencePosition[ i - superChrom ] ];
				for( int j = 1; j <= length; j++ )
						newIndividuals.chrom[ i ][ j ] = oldIndividuals.chrom[ oldExcellencePosition[ i - superChrom ] ][ j ];
		}


		// 2
		// ===========================================================================================

		//record elite
		for( int i = 1; i <= overBest; i++ )
		{
				newIndividuals.fitness[ i + sizePop ] = newIndividuals.fitness[ i ];
				newIndividuals.excellence[ i + sizePop ] = newIndividuals.excellence[ i ];
				newIndividuals.concentration[ i + sizePop ] = newIndividuals.concentration[ i ];
				for( int j = 1; j <= length; j++ )
						newIndividuals.chrom[ i + sizePop ][ j ] = newIndividuals.chrom[ i ][ j ];
		}


		// 3
		//copy back ==================================
		for( int i = 1; i <= M ; i++ )
		{
				oldIndividuals.fitness[ i ] = newIndividuals.fitness[ i ];
				oldIndividuals.excellence[ i ] = newIndividuals.excellence[ i ];
				oldIndividuals.concentration[ i ] = newIndividuals.concentration[ i ];
				for( int j = 1; j <= length; j++ )
						oldIndividuals.chrom[ i ][ j ] = newIndividuals.chrom[ i ][ j ];
		}
}



