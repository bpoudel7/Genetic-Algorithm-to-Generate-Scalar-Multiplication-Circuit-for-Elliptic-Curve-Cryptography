#include "Display.h"

void DisplayChromosome(int *chrom, int chromLen)
{
    int i;
    printf("\nChromosome is: ");
    for(i = 0; i < chromLen; i++)
    {
        printf("%d  ", chrom[i]);
    }                   
    printf("\n");
}

void DisplayPopulation(IPTR p, int popSize, int chromLen)
{
    int i;
    
    for(i = 0; i < popSize; i++)
    {
        DisplayChromosome(p[i].chrom, chromLen);
        printf("Fitness: %lf\n", p[i].fitness);                    
    }
}

