#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define L_RANGE -10000
#define H_RANGE 10000
#define SIZE 1024
#define TRIES 10

void writeMatrixInFile(char* filePath, double matrix[][SIZE]) {
    FILE *fp;
    fp = fopen(filePath, "w");
    if (fp == NULL) {
        perror("Error Opening Sad");
    } 
    fprintf(fp, "%d\n", SIZE);
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++)
            fprintf(fp, "%lf ", matrix[i][j]);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void readMatrixFromFile(char* filePath, double matrix[][SIZE], int size) {
    FILE *fp;
    fp = fopen(filePath, "r");
    if(fp == NULL) 
        perror("Error opening file");

    fscanf(fp, "%d", &size);

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++){
            fscanf(fp, "%lf", &matrix[i][j]);
            /*printf("%lf ", matrix[i][j]);*/
        }

    fclose(fp);
}

void filePrint(char* file) {

    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL) {
        perror("Error Opening, ):");
    } 

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }

    fclose(fp);
}


void matrixMultiplication(double matrixA[][SIZE], double matrixB[][SIZE], double matrixC[][SIZE]) {
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            matrixC[i][j] = 0;

            for(int k = 0; k < SIZE; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                /*printf("%lf * %lf =", matrixA[i][k], matrixB[k][j]);*/
                /*printf("%lf\n", matrixA[i][k] * matrixB[k][j]);*/
            }
        }

        /*if(i % 10 == 0)*/
            /*printf("Multiplication at %lf%%\n", ((double)i/SIZE*100));*/
    }
    /*printf("Multiplication completed 100%%\n");*/
}

int main() 
{
    srand(time(NULL));

    /*int size = 100;*/
    /*printRandom(size);*/

    /*filePrint("files/a.txt");*/
    
    //Generate a two files with a size x size random matrix in it.
    struct timespec inicio, fim;
    double oneTimeRun;
    double totalTimeRunned = 0;

    char filePath[20];
    char numStr[5];
    sprintf(numStr, "%d", SIZE);
    filePath[0] = 0;
    strcat(filePath, "files/time");
    strcat(filePath, numStr);
    strcat(filePath, ".txt");
    /*printf("%s\n", filePath);*/


    FILE *fp;
    fp = fopen(filePath, "wr");

    double (*matrixC)[SIZE] = malloc(sizeof(double[SIZE][SIZE]));
    double (*matrixB)[SIZE] = malloc(sizeof(double[SIZE][SIZE]));
    double (*matrixA)[SIZE] = malloc(sizeof(double[SIZE][SIZE]));
    for(int i = 0; i < TRIES + 1; i++) {

        clock_gettime(CLOCK_MONOTONIC, &inicio);
        /*printf("Reading Matrix A\n");*/
        readMatrixFromFile("files/matrixA.txt", matrixA, SIZE);

        /*printf("Reading Matrix B\n");*/
        readMatrixFromFile("files/matrixB.txt", matrixB, SIZE);

        /*printf("Multipling matrix A with matrix B\n");*/
        matrixMultiplication(matrixA, matrixB, matrixC);

        /*printf("Writing Matrix C in file\n");*/
        writeMatrixInFile("files/matrixC.txt", matrixC);
        clock_gettime(CLOCK_MONOTONIC, &fim);

        if(i == 0)
            continue;
        oneTimeRun = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
        printf("Time spent during on number %d run: %lfs\n", i , oneTimeRun);
        fprintf(fp, "Run %d: %lfs\n", i, oneTimeRun);
        totalTimeRunned += oneTimeRun;
    }
    printf("Time spent in total: %lfs\n", totalTimeRunned);
    printf("Average time spent per run: %lfs\n", (double)totalTimeRunned / TRIES);
    fprintf(fp, "Time spent in total: %lfs\n", totalTimeRunned);
    fprintf(fp, "Average time spent per run: %lfs\n", (double)totalTimeRunned / TRIES);
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}
