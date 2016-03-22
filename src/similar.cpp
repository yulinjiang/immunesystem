#include "../include/similar.h"

double similar( double individual1[], double individual2[] )
{
		double dRet = 0;

		//to do;
		int count = 0;

		for( int i = 1; i<= length; i++)
		{
				if( individual1[ i ] == individual2[ i ])
						count++;
		}
		
		dRet = count / length;

		return dRet;
}
