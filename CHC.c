#include "CHC.h"

/*
    Function to generate the bit position where the bits of two parents differ
*/

void GenBitDiffPos(int *P1, int *P2, int chromLen, int *xp1, int *xp2, int *hd1, int *hd2)
{
    int i, j = 0;
    *hd1 = 0;
    *hd2 = 0;
    
    for(i = 0; i < chromLen/2; i++)
    {
        if(P1[i] != P2[i])
        {
            *hd1    = *hd1 + 1;
            xp1[j++] = i;     
        }
    }
    
    j = 0;
    for(i = chromLen/2; i < chromLen; i++)
    {
        if(P1[i] != P2[i])
        {
            *hd2    = *hd2 + 1;
            xp2[j++] = i;     
        }
    }
    
}


/*
    Function to perform the Half Uniform Crossover
*/

void HUXOver(POPULATION *p, IPTR P1, IPTR P2, IPTR C1, IPTR C2)
{
    int *p1Ch = NULL, *p2Ch = NULL, *c1Ch = NULL, *c2Ch = NULL;
    
    int xp1[840], xp2[840]; //for HUX half of the non matching bits are swapped [840 = 1680/2]
    
    int hd1, hd2; //hamming distance between the parents
    
    int i;
    int ranIndex, flipIndex, ranIndexMut1, ranIndexMut2;
    
    double pRandXover = 0.0;
    
    double pRandMut = 0.0;
    
    p1Ch = P1->chrom;        
    p2Ch = P2->chrom;        
    c1Ch = C1->chrom;        
    c2Ch = C2->chrom;        
    

    
    pRandXover = (double) (rand()%1000000)/1000000.0; //generate a random number in (0,1)
    pRandMut   = (double) (rand()%1000000)/1000000.0; //generate a random number in (0,1)
    
    
    if(pRandXover <= p->pCross)
    {
        GenBitDiffPos(p1Ch, p2Ch, p->chromLen, xp1, xp2, &hd1, &hd2);                        
        
        //first copy the entire parents to the child
        for(i = 0; i < p->chromLen; i++)
        {
            c1Ch[i] = p1Ch[i];
            c2Ch[i] = p2Ch[i];
        }

        //for first part
        for(i = 0; i < hd1/2; i++)
        {
            ranIndex        = rand()%hd1;
            flipIndex       = xp1[ranIndex];
            c1Ch[flipIndex] = 1 - c1Ch[flipIndex];                 
            c2Ch[flipIndex] = 1 - c2Ch[flipIndex];                 
        }
        
        //for second part
        for(i = 0; i < hd2/2; i++)
        {
            ranIndex        = rand()%hd2;
            flipIndex       = xp2[ranIndex];
            c1Ch[flipIndex] = 1 - c1Ch[flipIndex];                 
            c2Ch[flipIndex] = 1 - c2Ch[flipIndex];                 
        }
        
        //mutation
        if(pRandMut <= p->pMut)
        {
            printf("\n******** MUTATION ********\n");
            ranIndexMut1 = rand()%CHROM_LEN;
            ranIndexMut2 = rand()%CHROM_LEN;
            
            c1Ch[ranIndexMut1] = 1 - c1Ch[ranIndexMut1]; 
            c2Ch[ranIndexMut2] = 1 - c2Ch[ranIndexMut2];     
        }
        
    }
    else
    {
        for(i = 0; i < p->chromLen; i++)
        {
            c1Ch[i] = p1Ch[i];
            c2Ch[i] = p2Ch[i];
        }
        
        //mutation
        if(pRandMut <= p->pMut)
        {
            printf("\n******** MUTATION ********\n");
            ranIndexMut1 = rand()%CHROM_LEN;
            ranIndexMut2 = rand()%CHROM_LEN;
            
            c1Ch[ranIndexMut1] = 1 - c1Ch[ranIndexMut1]; 
            c2Ch[ranIndexMut2] = 1 - c2Ch[ranIndexMut2];     
        }
        
    } 
    
}


