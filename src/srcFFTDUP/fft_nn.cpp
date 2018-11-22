#include "fann.h"
#include "parroto.h"
extern ParrotObserver parroto;

#include <cstdio>
#include <iostream>
#include "fourier.hpp"
#include <fstream>
#include <time.h>

static int* indices;
static int* indicesDUP; //varaivel duplicada

static Complex* x;
static Complex* xDUP; //variavel duplicada


static Complex* f;
static Complex* fDUP; //variavel duplicada

int main(int argc, char* argv[])
{
	int i ;
	int iDUP; //variavel duplicada
	int n 						= atoi(argv[1]);
	FILE * detectLog;
	std::string outputFilename 	= argv[2];
	detectLog = fopen("detectLog","w");
	// prepare the output file for writting the theta values
	std::ofstream outputFileHandler;


	outputFileHandler.open(outputFilename);
		 

	outputFileHandler.precision(5);

	// create the arrays
	x 		= (Complex*)malloc(n * sizeof (Complex));
	xDUP		= (Complex*)malloc(n * sizeof (Complex)); // variavel duplicada

	f 		= (Complex*)malloc(n * sizeof (Complex));
	fDUP		= (Complex*)malloc(n * sizeof (Complex)); // variavel duplicada

	indices = (int*)malloc(n * sizeof (int));
	indicesDUP = (int*)malloc(n * sizeof (int)); // variavel duplicada

	if(x == NULL || f == NULL || indices == NULL)
	{
		std::cout << "cannot allocate memory for the triangle coordinates!" << std::endl;
		return -1 ;
	}
	if(xDUP == NULL || fDUP == NULL || indicesDUP == NULL){
		std::cout << "cannot allocate memory for the triangle coordinates!DMR" << std::endl;
		return -2 ;	
	
	}

	int K = n;
	int KDUP = n; //variavel duplicada

	for(i = 0;i < K ; i++)
	{
		x[i].real = i;
		x[i].imag = 0 ;
	}


	//loop duplicado
	for (iDUP = 0; iDUP< KDUP; iDUP++){

		xDUP[iDUP].real = iDUP;
		xDUP[iDUP].imag = 0;

	}
	//fim loop duplicado

	radix2DitCooleyTykeyFft(K, indices, x, f) ;
	
	radix2DitCooleyTykeyFft(KDUP, indicesDUP, xDUP, fDUP) ;// chamada do duplicado

	for(i = 0;i < K ; i++)
	{	if(f[i].imag == fDUP[i].imag){
			outputFileHandler << f[i].real << " " << f[i].imag << std::endl;
		}
		else {
			outputFileHandler << f[i].real << " " << f[i].imag << std::endl;
			fprintf(detectLog," %d  %f   %f \n",i,f[i].imag,fDUP[i].imag);
		}
	}


	outputFileHandler.close();

	return 0 ;
}
