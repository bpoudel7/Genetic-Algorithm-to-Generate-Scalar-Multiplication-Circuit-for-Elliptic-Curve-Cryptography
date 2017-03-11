#ifndef EVAL_H_
#define EVAL_H_

#include "GA.h"

#define CHROM_LEN  1680
#define GATE_ID    3
#define IP_ID      4
#define GATE_COUNT 160

#define P 29
#define ARR_SZ 36

void DisplayBin(unsigned int *bin, int bitLen);
void ReverseStr(unsigned int *bin, unsigned int *revBin, int bitLen);
void Dec2Bin(unsigned int dec, unsigned int *bin);
int Bin2Dec(unsigned int *bin, int bitLen);
int GenGateOutput(unsigned int gateNum, int A, int B);
void GenID(unsigned int *bin, unsigned int *ip1ID, unsigned int *ip2ID, unsigned int *gID);
void GenerateCircuit(int *chrom, int chromLen, char *fName);
void CircuitOutput(int *chrom, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int *x3, unsigned int *y3);
unsigned int InverseModN(unsigned int a, int N);
unsigned int ModN(int a, unsigned int N);
void PointAddition(unsigned int xp, unsigned int yp, unsigned int xq, unsigned int yq, unsigned int *xr, unsigned int *yr);
int Verify(unsigned int *xPoints, unsigned int *yPoints, unsigned int x3, unsigned int y3);
int Eval(int *chrom);

#endif
