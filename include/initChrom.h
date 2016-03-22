#ifndef _INIT_CHROM_H
#define _INIT_CHROM_H

#include "individuals.h"
#include <math.h>

#define initChrom() (rand()%((upperBound-lowerBound)*(int)pow(10, precision)))/(pow(10, precision)/1.00011)-upperBound

#endif
