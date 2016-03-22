#include "../include/mutation.h"
#include "../include/initChrom.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define random() rand()%1000*0.001
#define unidrnd(x) rand()%x+1

void mutation( struct individuals& oldIndividuals )
{
		double pick;
		int position, index;

		for( int i = 1; i <= M; i++ )
		{
				pick = random();
				index = unidrnd( sizePop );

				if( pick > pMutation )
					continue;

				position = unidrnd( length );
				
				oldIndividuals.chrom[ index ][ position ] = initChrom();
		}
}
