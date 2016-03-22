#include "../include/concentration.h"

double concentration(struct individuals& newIndividual, int chrom)
{
		double dRet = 0;

		//to do 
		double chromConcentration = 0;
		double xsd = 0; 

		for( int i = 0; i <= M; i++ )
		{
			xsd=similar( newIndividual.chrom[ chrom ], newIndividual.chrom[ i ] );
			if( xsd>0.7 )
					chromConcentration++;
		}
		
		dRet = chromConcentration / M;
		return dRet;
}
