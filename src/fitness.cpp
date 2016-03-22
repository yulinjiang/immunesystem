#include "../include/fitness.h"
#include <math.h>

double fitness(struct individuals& newIndividuals, int chrom )
{
		double dRet = 0;;

		for( int i=1; i<=length; i++ )
		{
				double dTemp = newIndividuals.chrom[chrom][i];
				dRet += dTemp * dTemp;
		}
		return dRet;
}

double fitness1(struct individuals& newIndividuals, int chrom )
{
		double dRet = 0;

		double fit1 = 0;
		double fit2 = 1;

		for( int i = 1; i <= length; i++ )
		{
				double dTemp = newIndividuals.chrom[ chrom ][ i ];
				fit1 += fabs( dTemp );
		}
		for( int i = 1; i <= length; i++ )
		{
				double dTemp = newIndividuals.chrom[ chrom ][ i ];
				fit2 *= fabs( dTemp );
		}

		dRet = fit1 + fit2;
		return dRet;
}

double fitness2( struct individuals& newIndividuals, int chrom )
{
		double dRet = 0;
		
		double fit1 = 0;
		double fit = 0;

		for( int i = 0; i<= length; i++ )
		{
				for( int j = 1; j <= i; j++)
				{
						double dTemp = newIndividuals.chrom[ chrom ][ i ];
						fit1 += dTemp;
				}
				fit += fit1 * fit1;
		}
		return dRet;
}
