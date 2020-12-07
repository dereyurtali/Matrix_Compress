#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "compress.h"

#define M 6 // Matrisin satir sayisi.
#define N 6 // Matrisin sutun sayisi.



void compress_CRS(int **A, int *nz, int *col_ind, int *row_ptr){
    bool didFound = false;
    int i = 0;
    int j = 0;
    int counter = 0;
    
    
    // A DIZISINDEKI 0 OLMAYAN ELEMANLARIN ADEDINI BULUYORUZ.
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if((*(A[i]+j)) != 0){
                counter++;
            }
        }
    }

    counter = 0;
    
    // NZ, COL_IND VE ROW_PTR 'NIN ICINI DOLDURUYORUM.
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if((*(A[i]+j)) != 0){ // 0 olan sayılarda direk pas geçiyoruz.
                *(nz+counter) = *(A[i]+j);
                *(col_ind+counter) = j;
                if(!didFound){
                    *(row_ptr+i) = counter;
                    didFound = true;
                }
                counter++;
            }
        }
        didFound = false;
    }
    /*
    // NZ YI BASTIRIYORUM.
    printf("\nnz: \t");
    for (i = 0; i < counter; i++) {
        printf("%d\t",*(nz+i));
    }
    // NZ YI BASTIRIYORUM.
    printf("\n\ncol_ind: ");
    for (i = 0; i < counter; i++) {
        printf("%d\t",*(col_ind+i));
    }
    // NZ YI BASTIRIYORUM.
    printf("\n\nrow_ptr: ");
    for (i = 0; i < M; i++) {
        printf("%d\t",*(row_ptr+i));
    }
*/
}



int **decompress_CRS(int *nz, int *col_ind, int *row_ptr){
    int i, j, foo = 0;
    int **nA = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++){
        nA[i] = (int *)malloc(M * sizeof(int));
    }
    
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (*(col_ind + foo) == j) {
                if (foo != *(row_ptr+(i+1))){
                    *(nA[i]+j) = (int) *(nz+foo);
                    foo++;
                }else
                    *(nA[i]+j) = 0;
            }else
                *(nA[i]+j) = 0;
            
        }
    }
    return nA;
}
void compress_CCS(int **A, int *nz, int *row_ind, int *col_ptr){
    bool didFound = false;
    int i = 0;
    int j = 0;
    int counter = 0;
    
    
    // A DIZISINDEKI 0 OLMAYAN ELEMANLARIN ADEDINI BULUYORUZ.
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if((*(A[i]+j)) != 0){
                counter++;
            }
        }
    }

    counter = 0;
    
    // NZ, COL_IND VE ROW_PTR 'NIN ICINI DOLDURUYORUM.
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if((*(A[i]+j)) != 0){ // 0 olan sayılarda direk pas geçiyoruz.
                *(nz+counter) = *(A[i]+j);
                *(row_ind+counter) = j;
                if(!didFound){
                    *(col_ptr+i) = counter;
                    didFound = true;
                }
                counter++;
            }
        }
        didFound = false;
    }
}



int **decompress_CCS(int *nz, int *row_ind, int *col_ptr){
    int i, j, foo = 0;
    int **nA = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++){
        nA[i] = (int *)malloc(M * sizeof(int));
    }
    
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (*(row_ind + foo) == j) {
                if (foo != *(col_ptr+(i+1))){
                    *(nA[i]+j) = (int) *(nz+foo);
                    foo++;
                }else
                    *(nA[i]+j) = 0;
            }else
                *(nA[i]+j) = 0;
            
        }
    }
    return nA;
}

void compress_IJ(int **A, int *nz, int *rows, int *cols) {
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (*(A[i]+j) != 0) {
                nz[(M*i)+j] = *(A[i]+j);
                rows[(M*i)+j] = i;
                cols[(M*i)+j] = j;
            }
        }
    }
}

int** decompress_IJ(int *nz, int *rows, int *cols) {
    int i, j, sayac=0;
    int **nA = (int **)malloc(N * sizeof(int *));
    for (i = 0; i < N; i++){
        nA[i] = (int *)malloc(M * sizeof(int));
    }
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            if (*(rows+sayac) == i && *(cols+sayac) == j) {
                *(nA[i]+j) = *(nz+sayac);
                sayac++;
            } else {
                *(nA[i]+j) = 0;
            }
        }
    }
    return nA;
}


void print2DArray(int **A){
    printf("\n\n");
    int i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%d\t",*(A[i]+j));
        }
        printf("\n");
    }
    printf("\n\n");
}

int **generate2DArray(int m, int n){
    int i, j, sayi=0;
    int **A = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++){
        A[i] = (int *)malloc(m * sizeof(int));
    }
    
    // DİZİNİN İÇİNİ DOLDURMA
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            sayi = rand()%10;
            if(sayi % 3 == 0 || sayi % 5 == 0)
                sayi = 0;
            *(A[i]+j) = sayi;
        }
    }sayi=0;
    
    return A;
}
