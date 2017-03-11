#ifndef _GA_H
#define _GA_H

//include the header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

//some constants for chromosome representation

//define the crossover threshold for half uniform crossover
#define CHROM_LEN 1680 //length of chromosome
#define XOVER_TH  336  //20% of chromosome length
#define ELITE_NUM 80   //population that goes to next generation after restart
#define POP_SZ    600  //population size 
#define MAX_GEN   800 //maximum generation

//Individual definition
typedef struct{
    int     *chrom;
    double  fitness;
}INDIVIDUAL;

//defining a new pointer data type 
typedef INDIVIDUAL *IPTR;

//data structure to represent the population
typedef struct{
    IPTR op, sop; //parent individuals in population
    IPTR cp, scp; //child individual in population 
    IPTR np; //individuals selected for next generation
    
    int chromLen; //chromosome length
    int gen; //current generation
    
    double sumFitness;
    double max;
    double avg;
    double min;
    
    double pCross;
    double pMut;
    
    double highestEverFitness;
    int    highestEverGen;
    int    highestEverIndex;
    
    int maxGen;
    int popSize;
    int maxi;
    int mini;
                        
}POPULATION;

#endif

