#include "../include/excellence.h"
#include <stdio.h>

void excellence( struct individuals& newIndividuals )
{
		double sumFitness = 0; 
		double sumConcentration = 0;

		double Fitness[ M + 1 ];
		double concentration[ M + 1 ];

		for( int i = 1; i <= M; i++ )
		{
				Fitness[ i ] = 100.0 / newIndividuals.fitness[ i ];
				concentration[ i ] = 100.0 / newIndividuals.concentration[ i ];
		}

		for( int i = 1; i <= M; i++ )
		{
				sumFitness += Fitness[ i ];
				sumConcentration += concentration[ i ];
		}
		
		for( int i = 1; i <= M; i++ )
		{
				newIndividuals.excellence[ i ] = ( Fitness[ i ] / sumFitness ) * ps
						+ ( concentration[ i ] / sumConcentration  ) * ( 1.0 - ps ); 

				// printf("oldFitness:%f  Fitness:%f  concentration:%f excellence:%f\n", newIndividuals.fitness[ i ],  Fitness[ i ], newIndividuals.concentration[ i ], newIndividuals.excellence[ i ] );
		}
}

