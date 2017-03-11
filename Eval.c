#include "Eval.h"

void DisplayBin(unsigned int *bin, int bitLen)
{
    int i;
    //printf("\nBin Num: ");
    for(i = 0; i < bitLen; i++)
    {
        printf("%d", bin[i]);
    }
}


void ReverseStr(unsigned int *bin, unsigned int *revBin, int bitLen)
{
    int i;
    for(i = 0; i < bitLen; i++)
    {
        revBin[bitLen-i-1] = bin[i];
    }

}

void Dec2Bin(unsigned int dec, unsigned int *bin)
{
    int i=0;
    int rem;
    int N = (signed) dec;
    unsigned int revBin[5] = {0,0,0,0,0};
    
    while(N > 0)
    {
        rem = N%2;
        N   = N/2;
        revBin[i++] = rem;
    }
    
    ReverseStr(revBin, bin, 5);    
}


int Bin2Dec(unsigned int *bin, int bitLen)
{
    int i;
    int decValue = 0;
    for(i = 0; i < bitLen; i++)
    {
        decValue += bin[i] * pow(2, bitLen - 1 - i);
    }
    
    return (decValue);
}


int GenGateOutput(unsigned int gateNum, int A, int B)
{
    int out = 2;
    
    switch(gateNum)
    {
        
        case 0: //AND  
                out = A & B;
                break;
        
        case 1:  //OR
                out = A | B;
                break;
                
        case 2:  //XOR
                out = A ^ B;
                break;
                
        case 3:  //XNOR
                out = !(A ^ B);
                break;
                
        case 4:  //NAND
                out = !(A & B);
                break;
                
        case 5:  //NOR
                out = !(A | B);
                break;
                
        case 6:  //NOT
                out = !A;
                break;
                
        case 7:  //wire
                out = A;
                break;
                
        default: //
                out = 2;
                break;
    }
    
    return (out);        
}

void GenID(unsigned int *bin, unsigned int *ip1ID, unsigned int *ip2ID, unsigned int *gID)
{
    int i, j = 0;
    unsigned int ip1[IP_ID], ip2[IP_ID], g[GATE_ID];
    
    for(i = 0; i < IP_ID; i++)
    {
        ip1[i] = bin[j++];
    }
    for(i = 0; i < IP_ID; i++)
    {
        ip2[i] = bin[j++];
    }
    for(i = 0; i < GATE_ID; i++)
    {
        g[i] = bin[j++];
    }
    
    *ip1ID = (Bin2Dec(ip1, IP_ID))%10;
    *ip2ID = (Bin2Dec(ip2, IP_ID))%10;
    *gID   = Bin2Dec(g,   GATE_ID);
}


//////////////////////////////////////////////////////Log to the data file////////////////////////////////////////////////////////////////

void GenerateCircuit(int *chrom, int chromLen, char *fName)
{
    unsigned int Gate[160][11];     //16*10 gates
    
    unsigned int gateID, ipID1, ipID2;
    
    int i, j, k;
    
    int ch = 0;
    
    FILE *fptr;
    
    char storeID[10];
    
    fptr = fopen(fName, "a");
    if(fptr == NULL)
    {
        printf("\nError!!! File Appending Failed.\n");
    }
    
    
    for(i = 0; i < GATE_COUNT; i++)
    {
        if((i == 0) || (i % 16 == 0))
        {
            //printf("\nGate ID for interface: ");
            for(j = 0; j < GATE_ID; j++)
            {
                if(ch <= CHROM_LEN)
                {
                    Gate[i][j] = chrom[ch++];
                }
                else
                {
                    printf("\nError! ch exceed the CHROM_LEN\n");
                }
            }
        }
        else
        {
            //printf("\nGate ID for Internal: ");
            for(k = 0; k < (GATE_ID+IP_ID*2); k++)
            {
                if(ch <= CHROM_LEN)
                {
                    Gate[i][k] = chrom[ch++];
                }
                else
                {
                    printf("\nError! ch exceed the CHROM_LEN\n");
                }
            }
            //printf("\n");
        }
    }
    
    
    //for 10 rows 
    for(i = 0; i < 160; i = i + 16)
    {
        //printf("\n== %d ==\n", i);
        
        gateID = Bin2Dec(Gate[i], 3);
        sprintf(storeID, "||%d|", gateID);
        fprintf(fptr, "%s", storeID);
        
        for(j = i+1; j <= (i+15); j++)  //mismatch
        {
            GenID(Gate[j], &ipID1, &ipID2, &gateID);
            
            //printf("\n%d\n", j);
            
            //DisplayBin(Gate[j], 11);
            
            //printf("\nipID1 = %u \t ipID2 = %u \t gateID = %u\n", ipID1, ipID2, gateID);
            
            sprintf(storeID, "|%d|", ipID1);
            fprintf(fptr, "%s", storeID);
            
            sprintf(storeID, "|%d|", ipID2);
            fprintf(fptr, "%s", storeID);
            
            sprintf(storeID, "|%d|", gateID);
            fprintf(fptr, "%s", storeID);
        }
        
        fprintf(fptr, "\n\n");
    }
    
    fprintf(fptr, "\n=================================================================================================================\n");
    
    fclose(fptr);  
    
    //printf("\nEnd of the generate function\n"); 
}
////////////////////////////////////////////////////////Log to data file Ends//////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////Generated Circuit Output Calculation///////////////////////////////////////////////////

void CircuitOutput(int *chrom, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int *x3, unsigned int *y3)
{
    int gateOutput[GATE_COUNT];
    int gateIndex;
    
    unsigned int gateID;
    
    unsigned int Gate[160][11];
    int chromIndex = 0;
    int Index1 = 0, Index2 = 0, i;
    
    int cLevel, A, B;
    unsigned int AIndex, BIndex;
    
    unsigned int x1Bin[5], y1Bin[5], x2Bin[5], y2Bin[5];
    //unsigned int x3Bin[5], y3Bin[5];                            
    
    
    
    //convert decimal to binary
    Dec2Bin(x1, x1Bin);
    Dec2Bin(y1, y1Bin);
    Dec2Bin(x2, x2Bin);
    Dec2Bin(y2, y2Bin);
    
    //printf("\n(x1, y1) = (%u, %u) and (x2, y2) = (%u, %u)\n", x1, y1, x2, y2);
    //printf("\nBinary Conversion: \n");
    
    //printf("\nx1Bin: ");
    //DisplayBin(x1Bin, 5);
    
    //printf("\ny1Bin: ");
    //DisplayBin(y1Bin, 5);
    
    //printf("\nx2Bin: ");
    //DisplayBin(x2Bin, 5);
    
    //printf("\ny2Bin: ");
    //DisplayBin(y2Bin, 5);
    
    //for 160 gates, generate the decimal IDs of gates 
    for(gateIndex = 0; gateIndex < 160; gateIndex++)
    {
        //printf("\ngateCount = %d\n", gateIndex);
        if(gateIndex == 0 || gateIndex % 16 == 0)
        {
            for(i = 0; i < 3; i++)
            {
                //printf("\nchromIndex = %d\n", chromIndex);
                Gate[gateIndex][i] = chrom[chromIndex++];
            }
        }
        else
        {
            for(i = 0; i < 11; i++)
            {
                //printf("\nchromIndex = %d\n", chromIndex);
                Gate[gateIndex][i] = chrom[chromIndex++];
            }
        }
    }   
    
    
    Index1 = 0; Index2 = 0;
    //generate the output of the interface gates
    //printf("\nCircuit Level = 0\n"); 
    for(gateIndex = 0; gateIndex < 160; gateIndex += 16)
    {
        gateID = Bin2Dec(Gate[gateIndex], 3);
        //printf("\ngateID: %d\n", gateID);
        if(gateIndex < 80)
        {
            A = x1Bin[Index1];
            B = y1Bin[Index1];
            Index1++;
            gateOutput[gateIndex] = GenGateOutput(gateID, A, B);
            //printf("\nA = %d gateID = %d B = %d : %d\n", A, gateID, B, gateOutput[gateIndex]);      
        }
        else
        {
            A = x2Bin[Index2];
            B = y2Bin[Index2];
            Index2++;
            gateOutput[gateIndex] = GenGateOutput(gateID, A, B);
            //printf("\nA = %d gateID = %d B = %d : %d\n", A, gateID, B, gateOutput[gateIndex]);      
        }
    }
    
    //generate the output for the rest of the gates: Level 1 to Level 15 
    //numbering is row wise; first row goes from 0 to 15; second from 16 to 31, and so on
    for(cLevel = 1; cLevel <= 15; cLevel++)
    {
        //printf("\nCircuit Level = %d\n", cLevel);
        for(gateIndex = cLevel; gateIndex < 160; gateIndex += 16)
        {
            GenID(Gate[gateIndex], &AIndex, &BIndex, &gateID);
            Index1 = AIndex*16+(cLevel-1);
            Index2 = BIndex*16+(cLevel-1);
            
            //printf("\nIndex1 = %d and Index2 = %d\n", Index1, Index2);
            
            A = gateOutput[Index1];
            B = gateOutput[Index2];
            gateOutput[gateIndex] = GenGateOutput(gateID, A, B);
            //printf("\nA = %d gateID = %d B = %d : %d\n", A, gateID, B, gateOutput[gateIndex]);      
        }
    }
    
    //generate the output
    *x3 = gateOutput[15]  * pow(2,4) + gateOutput[31] * pow(2,3) + gateOutput[47] * pow(2,2) + gateOutput[63] * pow(2,1) + gateOutput[79]; 
    *y3 = gateOutput[95] * pow(2,4) + gateOutput[111] * pow(2,3) + gateOutput[127] * pow(2,2) + gateOutput[143] * pow(2,1) + gateOutput[159]; 
}
/////////////////////////////////////////////////Generated Circuit Output Calculation///////////////////////////////////////////////////////



/////////////////////////////////////////////Expected Output Calculation///////////////////////////////////////////////////////////////////

/* Extended Euclidean Algorithm to find inv(a) mod N */
unsigned int InverseModN(unsigned int a, int N)
{
	int t = 0, 
	    r = N, 
	    newt = 1, 
		newr = (signed)a;
	int temp;
	
	int quotient;
	
	while(newr != 0)
	{
		quotient = r/newr;
		temp 	= newt;
		newt 	= t - quotient * newt;    
		t  		= temp;
		temp 	= newr; 
		newr  	= r - quotient * newr;
		r 		= temp;
	}
	
	if(r > 1)
		printf("\n%d is not invertible!!!\n", a);
	
	if(t < 0)
		t = t + N;
	
	//printf("\nInverse of %d mod % d = %d\n", a, N, t);
	
	return (unsigned)t;
}


unsigned int ModN(int a, unsigned int N)
{
    int result;
	
	result = a - ((a/(signed)N) * (signed)N);
	
	if(result < 0)
		result = result + N;
	
	//printf("\n%d mod %d = %d\n", a, N, result);
	
	return ((unsigned) result);
}

void PointAddition(unsigned int xp, unsigned int yp, unsigned int xq, unsigned int yq, unsigned int *xr, unsigned int *yr)
{
    unsigned int lambda;
	unsigned int xdiff, ydiff;
	unsigned inv;
	
	xdiff = ModN((xq - xp), P);
	ydiff = ModN((yq - yp), P);
	
	inv = InverseModN(xdiff, P);
	
	lambda = ModN((ydiff * inv), P);
	
	//printf("\nlambda = %u\n", lambda);
	
	*xr = ModN((ModN((lambda * lambda), P) - (ModN((xp + xq), P))), P);
	
	*yr = ModN(((lambda * ModN((xp - *xr), P)) - yp), P); 
	
}

int Verify(unsigned int *xPoints, unsigned int *yPoints, unsigned int x3, unsigned int y3)
{
    int i;
    
    for(i = 0; i < ARR_SZ; i++)
    {
        if((x3 == xPoints[i]) && (y3 == yPoints[i]))
        {
            return (1);
        }
    }
    
    return (0);
}


///////////////////////////////////////////////Expected Output Calculation Ends/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////Eval Function////////////////////////////////////////////////////////////////////////////////////////////////

int Eval(int *chrom)
{
    unsigned int xPoints[36] = {2, 4,  8,  13, 16, 19, 27, 0, 2,  5, 8,  14, 16, 20, 27, 0,  3, 5,  10, 14, 17, 20, 1, 3,  6,  10, 15, 17, 24, 1,  4,  6,  13, 15, 19, 24};
    unsigned int yPoints[36] = {6, 19, 10, 23, 2,  16, 2,  7, 23, 7, 19, 6,  27, 3,  27, 22, 1, 22, 4,  23, 10, 26, 5, 28, 12, 25, 2,  19, 7,  24, 10, 17, 6,  27, 13, 22}; 
    
    unsigned int x1, y1, x2, y2; 
    unsigned int x3Exp, y3Exp, x3Obt, y3Obt;
    
    int i, j;
    
    int fitness = 0;
    
    for(i = 0; i < ARR_SZ; i++)
    {
        x1 = xPoints[i];
        y1 = yPoints[i];
        
        for(j = 0; j < ARR_SZ; j++)
        {   
            if(i != j)
            {
                x2 = xPoints[j];
                y2 = yPoints[j];
                
                if(x1 == x2)
                {
                    continue;
                }
                
                //Expected output calculation
                PointAddition(x1, y1, x2, y2, &x3Exp, &y3Exp);
                
                //Circuit output calculation
                CircuitOutput(chrom, x1, y1, x2, y2, &x3Obt, &y3Obt);
                
                if(Verify(xPoints, yPoints, x3Exp, y3Exp))
                {
                    //printf("\n(%d,%d) + (%d,%d) = (%d,%d):", x1, y1, x2, y2, x3Exp, y3Exp);
                    //printf("\tSuccessful Verification.\n");
                    
                    if(x3Exp == x3Obt && y3Exp != y3Obt)
                    {
                        //printf("\nx3Exp == x3Obt\n");
                        fitness += 10;    
                    }
                    else if(x3Exp != x3Obt && y3Exp == y3Obt)
                    {
                        //printf("\ny3Exp == y3Obt\n");
                        fitness += 10;
                    }
                    else if(x3Exp == x3Obt && y3Exp == y3Obt)
                    {
                        //printf("\nboth same\n");
                        fitness += 100;
                    }
                    else
                    {
                        //printf("\n both different \n");
                        fitness += 0;
                    }
                }
                else
                {
                   // printf("\n(%d,%d) + (%d,%d) = (%d,%d):", x1, y1, x2, y2, x3Exp, y3Exp);
                    printf("\t!!!ERROR!!! The result does not lies in curve.\n");
                }
            }
        }
    }
    
    return (fitness);
          
}


///////////////////////////////////////////////Eval Function Ends///////////////////////////////////////////////////////////////////////////////////////////


