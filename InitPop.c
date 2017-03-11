#include "InitPop.h"

/*
    Initialize a random population to start
*/

void InitPop(POPULATION *p,        // current population
             double pc,           // pCross
             double pm,          // pMut
             int    cl,         // chromosome length
             int    ps,        // population size
             int    mg        // maximum generation
             )
{
    IPTR pi, pj, pk, psi, psj;
    int  i, j;
    
    
    p->pCross   = pc;
    p->pMut     = pm;
    p->chromLen = cl;
    p->popSize  = ps;
    p->maxGen   = mg;
    
    /*Set progress indicator to zero*/
    p->highestEverFitness = 0.0; 
    p->highestEverGen     = 0;
    p->highestEverIndex   = 0;
    p->gen                = 0;
    p->maxi               = 0;
    p->mini               = 0;
    
    p->op = (IPTR) calloc(p->popSize, sizeof(INDIVIDUAL));
    p->cp = (IPTR) calloc(p->popSize, sizeof(INDIVIDUAL));
    p->np = (IPTR) calloc(p->popSize, sizeof(INDIVIDUAL));
    
    p->sop = (IPTR) calloc(p->popSize, sizeof(INDIVIDUAL));
    p->scp = (IPTR) calloc(p->popSize, sizeof(INDIVIDUAL));
    
    p->sumFitness = 0.0;
    
    for(i = 0; i < p->popSize; i++)
    {
        pi = &(p->op[i]);
        pi->chrom = (int*) calloc(p->chromLen, sizeof(int));
        
        psi = &(p->sop[i]);
        psi->chrom = (int*) calloc(p->chromLen, sizeof(int));
        
        pj = &(p->cp[i]);
        pj->chrom = (int*) calloc(p->chromLen, sizeof(int));
        
        psj = &(p->scp[i]);
        psj->chrom = (int*) calloc(p->chromLen, sizeof(int));
        
        pk = &(p->np[i]);
        pk->chrom = (int*) calloc(p->chromLen, sizeof(int));
        
        for(j = 0; j < p->chromLen; j++)
        {
            pi->chrom[j] = rand()%2;
        }
        
        pi->fitness = Eval(&(pi->chrom[0]));
        //pi->fitness = rand()%100;
        p->sumFitness += pi->fitness;
    }
}

