#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define L_RANGE -10000
#define H_RANGE 10000
#define SIZE 2048



int randomFA(double min, double max) {
    return rand() * (max - min) / (double)RAND_MAX + min;
}


double randomF(double min, double max) {
    return (double)rand() * (max - min) / (double)RAND_MAX + min;
}

void printRandom(int size) {
    for (int i = 0; i < size; i++) {
        printf("%f , ", randomF(L_RANGE, H_RANGE));
    }
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
    /*printf("Generating Matrix A\n");*/
    /*writeRandomMatrixInFile("files/matrixA.txt", SIZE);*/
    /*printf("Generating Matrix B\n"); */
    /*writeRandomMatrixInFile("files/matrixB.txt", SIZE);*/

    double (*matrixA)[SIZE] = malloc(sizeof(double[SIZE][SIZE]));
    readMatrixFromFile("files/matrixA.txt", matrixA, SIZE);

    double (*matrixB)[SIZE] = malloc(sizeof(double[SIZE][SIZE]));
    readMatrixFromFile("files/matrixB.txt", matrixB, SIZE);

    double (*matrixC)[SIZE] = malloc(sizeof(double[SIZE][SIZE]));
    matrixMultiplication(matrixA, matrixB, matrixC);

    printf("Writing Matrix C in file\n");
    writeMatrixInFile("files/matrixC.txt", matrixC);

    free(matrixA);
    free(matrixB);
    free(matrixC);
    return 0;
}
