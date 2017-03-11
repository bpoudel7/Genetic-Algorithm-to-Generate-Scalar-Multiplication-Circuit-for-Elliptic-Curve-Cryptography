#ifndef Generate_h_
#define Generate_h_

#include "GA.h"
#include "CHC.h"
#include "Display.h"
#include "Eval.h"

void GenerateNewPop(POPULATION *p);
int CheckIncest(int *p1, int *p2, int chromLen);
int Roulette(IPTR pop, double sumFitness, int popsize);
void EliteSelection(POPULATION *p);

#endif


