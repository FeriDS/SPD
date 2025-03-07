#include <bits/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define L_RANGE -10000
#define H_RANGE 10000
#define SIZE 2048
#define TRIES 10

double randomF(double min, double max) {
    return (double)rand() * (max - min) / (double)RAND_MAX + min;
}

void writeRandomMatrixInFile(char* filePath, int size) {
    FILE *fp;
    fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Error Opening Sad");
    } 
    /*char *str[100];*/
    fprintf(fp, "%d\n", size);
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            fprintf(fp, "%lf ", randomF(L_RANGE, H_RANGE));
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main(){

    printf("Generating Matrix A\n");
    writeRandomMatrixInFile("files/matrixA.txt", SIZE);
    printf("Generating Matrix B\n"); 
    writeRandomMatrixInFile("files/matrixB.txt", SIZE);
}
