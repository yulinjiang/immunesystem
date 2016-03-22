#ifndef _INDIVIDUALS_H
#define _INDIVIDUALS_H

const int sizePop = 30;
const int overBest = 10;
const int maxGen = 2000;
const int length = 20;
const int M = sizePop + overBest;

const double pCross = 0.5;
const double pMutation = 0.6;
const double ps = 0.5;

const int upperBound = 100;
const int lowerBound = -100;
const int precision = 6;


#define FITNESS 0
#define CONCENTRATION 1
#define EXCELLENCE 2
#define CHROM 3
#define ALL 4

struct individuals{
		double fitness [ M + 1 ];
		double concentration [ M + 1 ];
		double excellence [ M + 1 ];
		double chrom [ M + 1 ] [ length + 1 ];
};

#endif
