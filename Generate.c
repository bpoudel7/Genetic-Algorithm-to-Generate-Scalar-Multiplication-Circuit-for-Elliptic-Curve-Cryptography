#include "Generate.h"
#include "Eval.h"


int CheckIncest(int *p1, int *p2, int chromLen)
{
    int i, hamDist = 0;
    for(i = 0; i < chromLen; i++)
    {
        if(p1[i] != p2[i])
        {
            hamDist++;
        }
    }       
    
    if(hamDist >= XOVER_TH)
    {
        return (1);
    }
    else
    {
        return (0);
    }
    
}

/*
   select a single individual by roulette wheel selection, fitness proportional selection     
*/

int Roulette(IPTR pop, double sumFitness, int popsize)
{
    double prob021, 
           randNum, 
           partsum;
    int i;

    partsum = 0.0; 
    i = 0;

    prob021 = (double) (rand()%1000000)/1000000.0;

    randNum = prob021 * sumFitness; 

    i = -1;
    do
    {
        i++;
        partsum += pop[i].fitness;
    } 
    while (partsum < randNum && i < popsize - 1);

    return i;        
    
    
}


/*
    Function that generates a new population
*/
void GenerateNewPop(POPULATION *p)
{
    //printf("\n---GenerateNewPop Start---\n");
    
    IPTR p1, p2, c1, c2;
    
    char ErrorFile[20] =  "ErrorLog.txt";
        
    FILE *fptr;
    
    fptr = fopen(ErrorFile, "a");
    if(fptr == NULL)
    {
        printf("\nGenerateNewPop() Error Line 87: ERROR in appending data file.\n");
    }
    
    
    int selectP1, selectP2;
    
    int i;
    
    int countFails = 0;
    
    for(i = 0; i < p->popSize; i+= 2)
    {
        //printf("\n *************************** GenerateNewPop(): population = %d *************************** \n", i);
        countFails = 0;
        //engage in this loop until we find the two individuals that have hamming distance more than XOVER_TH
        do
        {        
            selectP1 = Roulette(p->op, p->sumFitness, p->popSize);
            selectP2 = Roulette(p->op, p->sumFitness, p->popSize);

            p1 = &(p->op[selectP1]);
            p2 = &(p->op[selectP2]);
            
            countFails++;
            
            if(countFails >= POP_SZ)
            {
                fprintf(fptr, "\n*********************************************************\n");
                fprintf(fptr, "\n********** NO CROSSOVER FOR ENTIRE POPULATION ***********\n");
                fprintf(fptr, "\n*********************************************************\n");
            }
        
        }
        while(CheckIncest(p1->chrom, p2->chrom, p->chromLen) != 1);
        
        printf("\n---- Number of times the crossover pair fails = %d ----\n", countFails-1);
        
        c1 = &(p->cp[i]);
        c2 = &(p->cp[i+1]);
        
        HUXOver(p, p1, p2, c1, c2);    
        
        c1->fitness = Eval(&(c1->chrom[0]));
        c2->fitness = Eval(&(c2->chrom[0]));
    }
    
    fclose(fptr);
    
}


/*
    Elitist Selection from the pool of the parent and children
*/
void EliteSelection(POPULATION *p)
{
    //IPTR pi, ci;
    IPTR psi, csi, ni;
    
    double tempFit;
    double tempChrom;
    
    int i, j, k;
    
    //====================== copy the parents and child in temp ====================================
    
    p->sop = p->op;
    p->scp = p->cp;        
    
    ni  = &(p->np[0]);
    
    psi = &(p->sop[0]); 
    csi = &(p->scp[0]); 
    
    //====================== Sorting the individual with highest fitness ===========================
    
    for(i = 0; i < p->popSize; i++)
    {
        for(j = i+1; j < p->popSize; j++)
        {
            if(psi[i].fitness < psi[j].fitness)
            {
                for(k = 0; k < p->chromLen; k++)
                {
                    tempChrom       = psi[i].chrom[k];    
                    psi[i].chrom[k] = psi[j].chrom[k];
                    psi[j].chrom[k] = tempChrom;
                }
                
                tempFit        = psi[i].fitness;
                psi[i].fitness = psi[j].fitness;
                psi[j].fitness = tempFit;    
            } 
            
            if(csi[i].fitness < csi[j].fitness)
            {
                for(k = 0; k < p->chromLen; k++)
                {
                    tempChrom       = csi[i].chrom[k];    
                    csi[i].chrom[k] = csi[j].chrom[k];
                    csi[j].chrom[k] = tempChrom;
                }
                
                tempFit        = csi[i].fitness;
                csi[i].fitness = csi[j].fitness;
                csi[j].fitness = tempFit;    
            }
               
        }
    }                          
    
    
    //====================== Select best 10% =============================================
    
    j = 0;
    
    for(i = 0; i < ELITE_NUM/2; i++)
    {
        for(k = 0; k < p->chromLen; k++)
        {
            ni[j].chrom[k] = psi[i].chrom[k];    
        }
        ni[j].fitness = psi[i].fitness;
        j++;
    }
    
    
    for(i = 0; i < ELITE_NUM/2; i++)
    {
        for(k = 0; k < p->chromLen; k++)
        {
            ni[j].chrom[k] = csi[i].chrom[k];    
        }
        ni[j].fitness = csi[i].fitness;
        j++;
    }
    
    
    //====================== ends ========================================================
    
    
    //====================== remaining are best 90% of child population ==================
    
    for(i = ELITE_NUM; i < p->popSize; i++)
    {
        for(k = 0; k < p->chromLen; k++)
        {
            ni[j].chrom[k] = csi[i].chrom[k];    
        }
        ni[j].fitness = csi[i].fitness;
        j++;
    }
    
    //====================== ends ========================================================
    
}



