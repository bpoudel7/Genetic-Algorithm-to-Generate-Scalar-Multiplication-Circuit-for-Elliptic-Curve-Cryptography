ECPAGA: ECPAGA.c InitPop.o CHC.o Generate.o Statistics.o Display.o Eval.o
	g++ -Wall -o ECPAGA ECPAGA.c InitPop.o CHC.o Generate.o Display.o Statistics.o Eval.o 
	 
InitPop.o: InitPop.c InitPop.h GA.h
	g++ -Wall -c InitPop.c  

CHC.o: CHC.c CHC.h GA.h
	g++ -Wall -c CHC.c

Generate.o: Generate.c Generate.h GA.h CHC.h 		
	g++ -Wall -c Generate.c

Statistics.o: Statistics.c Statistics.h Eval.h GA.h
	g++ -Wall -c Statistics.c 

Display.o: Display.c Display.h GA.h
	g++ -Wall -c Display.c 	

Eval.o: Eval.c Eval.h GA.h
	g++ -Wall -c Eval.c 	
clean:
	rm *.o ECPAGA logFile.txt cktFile.txt	
