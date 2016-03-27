#include "../include/select.h"
#include "../include/initChrom.h"
#include <stdlib.h>

#include <time.h>
#include <stdio.h>

void select( struct individuals& oldIndividuals )
{
		struct individuals newIndividuals;
		int index[ sizePop + 1 ];

		double pick;
		double sumExcellence = 0;
		double pSelect[ sizePop + 1 ];
		int selectFlag[ sizePop + 1 ];

		for( int i = 1; i <= sizePop; i++ )
				sumExcellence += oldIndividuals.excellence[ i ];

		for( int i = 1; i <= sizePop; i++ )
		{
				pSelect[ i ] = oldIndividuals.excellence[ i ] / sumExcellence;
				selectFlag[ i ] = 0;
		}

		//select by probility..
		pick = (  rand( )%100000 ) * 0.00001;
		for( int i = 1; i <= sizePop; i++ )
		{
				pick = (  rand( )%100000 ) * 0.00001;

				while (  pick < 0.01 )
						pick = (  rand( )%100000 ) * 0.00001 ;


				for( int j = 1; j <= sizePop; j++ )
				{
						pick = pick - pSelect[ j ];

						if( pick < 0.0001 )
						{
								index[ i ] = j;
								selectFlag[ j ]++;
								break;
						}
				}
		}

		//select chorm...
		for( int i = 1; i <= sizePop; i++ )
		{
				newIndividuals.fitness[ i ] = oldIndividuals.fitness[ index[ i ] ];
				newIndividuals.concentration[ i ] = oldIndividuals.concentration[ index[ i ] ];
				newIndividuals.excellence[ i ] = oldIndividuals.excellence[ index[ i ] ];
				
				for( int j = 1; j <= length; j++ )
				{
						newIndividuals.chrom[ i ][ j ] = oldIndividuals.chrom[ index[ i ] ][ j ];
				}
		}

		//copy back
		for( int i = 1; i <= sizePop; i++ )
		{
				oldIndividuals.fitness[ i ] = newIndividuals.fitness[ i ];
				oldIndividuals.concentration[ i ] = newIndividuals.concentration[ i ];
				oldIndividuals.excellence[ i ] = newIndividuals.excellence[ i ];
				
				for( int j = 1; j <= length; j++ )
				{
						oldIndividuals.chrom[ i ][ j ] = newIndividuals.chrom[ i ][ j ];
				}
		}
		//adjust chrom

}
