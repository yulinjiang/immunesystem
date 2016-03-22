#include "../include/cross.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define random() rand()%1000*0.001
#define unidrnd(x) rand()%x+1

void cross( struct individuals& oldIndividuals )
{
		double pick;

		int index_1, index_2;
		int position;
		double tempChrom[ length + 1 ];

		for( int i = 1; i <= sizePop; i++ )
		{
				pick = random();
				
				if( pick > pCross )
						continue;

				index_1 = unidrnd( sizePop );
				index_2 = unidrnd( sizePop );

				while( index_1 == index_2 )
						index_2 = unidrnd( sizePop );

				position = unidrnd( length );
				while( position == 1 )
						position = unidrnd( length );

				for( int i = position; i<= length; i++ )
				{
						tempChrom[ i ] = oldIndividuals.chrom[ index_1 ][ i ];
						oldIndividuals.chrom[ index_1 ][ i ] = oldIndividuals.chrom[ index_2 ][ i ];
						oldIndividuals.chrom[ index_2 ][ i ] = tempChrom[ i ];
				}

		}
}
