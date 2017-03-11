#include "Statistics.h"

/*
    Function to generate a statistical report of current population and store in text file    
*/
void Statistics(POPULATION *p, IPTR currentPop, char *fname1, char *fname2)
{
    int i;
    
    FILE *fptr1;
    
    int *chrom;
    
    //=================== computation part ==========================
        
    p->sumFitness = currentPop[0].fitness;
    p->max        = p->sumFitness;
    p->min        = p->sumFitness;
    p->avg        = p->sumFitness;
    
    for(i = 1; i < p->popSize; i++)
    {
        p->sumFitness += currentPop[i].fitness;
        
        if(p->max < currentPop[i].fitness)
        {
            p->max = currentPop[i].fitness; 
            p->maxi = i;
        }
        
        if(p->max > currentPop[i].fitness)
        {
            p->min = currentPop[i].fitness; 
            p->mini = i;
        }
    }
    
    p->avg = p->sumFitness/(double) p->popSize;
    
    if(p->highestEverFitness < p->max)
    {
        p->highestEverFitness = p->max;
        p->highestEverGen     = p->gen;
        p->highestEverIndex   = p->maxi;
    }
    
    //================ computation part ends =====================
    
    //================ recording the statistics ==================
    
    fptr1 = fopen(fname1, "a");
    if(fptr1 == NULL)
    {
        printf("\nError in appending file!!!\n");
    }
    
    fprintf(fptr1, "%4d, %3.4lf, %3.4lf, %3.4lf", p->gen, p->max, p->min, p->avg);
    fprintf(fptr1, "\n");
    fclose(fptr1);
    
    
    //record the coalitions
        
    chrom = &(currentPop[p->maxi].chrom[0]);
    GenerateCircuit(chrom, CHROM_LEN, fname2);
    
    //================ record ends ===============================
}




