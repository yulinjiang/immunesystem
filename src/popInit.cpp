#include "../include/popInit.h"
#include "../include/initChrom.h"
#include <stdlib.h>
#include <time.h>

int popInit( struct individuals& newIndividuals )
{                                                                                                                
        for ( int i = 1; i<= M; i++ )                                                                            
        {                                                                                                        
                for( int j = 1;j <= length; j++ )                                                                
                {                                                                                                
                        newIndividuals.chrom[i][j] = initChrom();                                        
                }                                                                                                
        }                                                                                                        
        return 0;                                                                                                
}
