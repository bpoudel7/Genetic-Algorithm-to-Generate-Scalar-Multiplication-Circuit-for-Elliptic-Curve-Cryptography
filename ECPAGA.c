#ifndef GtUAV_H_
#define GtUAV_H_

#include "GA.h"
#include "InitPop.h"
#include "CHC.h"
#include "Generate.h"
#include "Display.h"
#include "Statistics.h"

#endif


int main(void)
{
    POPULATION population;
    
    POPULATION *p = &population;
    
    //IPTR p1, c1, n1;
    
    IPTR temp;
    
    //int i;
    char statFile[50] = "logFile.txt";
    char cktFile[50] = "cktFile.txt";
    
    double pCross = 0.80;
    double pMut   = 0.001;
    
    int chromLen  = CHROM_LEN,
        popSize   = POP_SZ, //must ALWAYS BE EVEN
        maxGen    = MAX_GEN;
    /*
    double avgMaxFit[100],
           avgMinFit[100],
           avgAvgFit[100];        
    */
    
    time_t tSec;
    
    /*Initialize the random number generator*/
    srand((unsigned int) time(&tSec));
    
    p->gen = 0;
    
    
    //printf("\n-- Before INIT ---\n");
    InitPop(p, pCross, pMut, chromLen, popSize, maxGen); 
    //printf("\n-- after init ---\n");
    
    while(p->gen < p->maxGen)
    {
    
        printf("\n== Generation: %d ==\n", p->gen);
        
        //printf("\n--Before GenerateNewPop()--\n");
        GenerateNewPop(p);
        //printf("\n--After GenerateNewPop()--\n");
        
        //printf("\n--Before EliteSelection()--\n");
        EliteSelection(p); 
        //printf("\n--After EliteSelection()--\n");
        
        //printf("\n--Before Statistics()--\n");
        /* Generate the statistical report */
        Statistics(p, p->np, statFile, cktFile);
        //printf("\n--After Statsitics()--\n");
        
        temp  = p->op;
        p->op = p->np;
        p->np = temp; 
        
        p->gen++;
        
    }
    
    //Best Chromosome 
    
    
    
    return 0;                            
}


