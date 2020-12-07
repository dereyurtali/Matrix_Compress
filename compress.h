#ifndef compress_h
#define compress_h

#include <stdio.h>
#include <stdlib.h>

#endif /* compress_h */






// SATIR SIKISTIRMA ALGORITMASI
void compress_CRS(int **, int *, int *, int *);// SIKISTIR
int **decompress_CRS(int *, int *, int *); // GERI AC



// SUTUN SIKISTIRMA ALGORITMASI
void compress_CCS(int **, int *, int *, int *);

int **decompress_CCS(int *, int *, int *);




int **generate2DArray(int, int);

void print2DArray(int **);
