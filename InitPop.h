#ifndef __INITPOP_H_
#define __INITPOP_H_ 

#include "GA.h"
#include "Eval.h"

void InitPop(POPULATION *p,        // current population
             double pc,           // pCross
             double pm,          // pMut
             int    cl,         // chromosome length
             int    ps,        // population size
             int    mg        // maximum generation
             );

#endif

             
