#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "compress.h"

#define M 6 // Matrisin satir sayisi.
#define N 6 // Matrisin sutun sayisi.


int main(void) {
    srand((unsigned int)time(NULL));
    int i, j, sayi=0;
    int *nz, *col_ind, *row_ptr, *rows, *cols;
    
    // DİZİYİ OLUŞTURMA VE YER AYIRMA
    int **A = generate2DArray(M, N);
    int **nA = generate2DArray(M, N);
    
    
    // ROW_PRT ICIN YER OLUSTURDUM.
    row_ptr = (int *)malloc((M+1)*sizeof(int));
    
    rows = (int *)malloc(M*sizeof(int));
    cols = (int *)malloc(N*sizeof(int));
    
    // A DIZISINDEKI 0 OLMAYAN ELEMANLARIN ADEDINI BULUYORUZ.
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if((*(A[i]+j)) != 0){
                sayi++;
            }
        }
    }
    
    // A DIZISINDEKI 0 OLMAYAN ELEMAN SAYISI KADAR NZ ICIN YER OLUSTURDUM.
    nz = (int *)malloc(sayi*sizeof(int));
    // COL_IND DIZISININ ELEMAN SAYISI NZ ILE AYNI OLACAK O YUZDEN ONUN ICIN DE YER OLUSTURDUM.
    col_ind = (int *)malloc(sayi*sizeof(int));
    
    printf("Original Array: \n");
    print2DArray(A);
    
    compress_CRS(A, nz, col_ind, row_ptr);
    nA = decompress_CRS(nz, col_ind, row_ptr);
    printf("Compressed and Decompressed w/CRS Method: \n");
    print2DArray(nA);
    
    compress_CCS(A, nz, col_ind, row_ptr);
    nA = decompress_CCS(nz, col_ind, row_ptr);
    printf("Compressed and Decompressed w/CCS Method: \n");
    print2DArray(nA);
    
    compress_IJ(A, nz, col_ind, row_ptr);
    nA = decompress_IJ(nz, col_ind, row_ptr);
    printf("Compressed and Decompressed w/IJ Coordinate Compression Method: \n");
    print2DArray(nA);
    
    return 0;
}
