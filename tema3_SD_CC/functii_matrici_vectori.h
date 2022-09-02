#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_d_vector(int *vector, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        vector[i] = -1;
    }
}

void init_f_vector(float *vector, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        vector[i] = -1;
    }
}

void print_d_while(int *vector, int n, int stop)
{
    int i = 0;
    while (i < n)
    {
        if (vector[i] != stop)
        {
            printf("%d ", vector[i]);
        }
        if (vector[i] == stop)
        {
            printf("%d ", stop);
            break;
        }
        i = i + 1;
    }
}

void matrix_f_printer(float **matrix, int randuri, int coloane)
{
    int i, j;
    for (i = 0; i < randuri; i++)
    {
        for (j = 0; j < coloane; j++)
        {
            printf("%0.1f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_d_printer(int **matrix, int randuri, int coloane)
{
    int i, j;
    for (i = 0; i < randuri; i++)
    {
        for (j = 0; j < coloane; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_int_matrix(int **matrix, int randuri)
{
    int i;
    for (i = 0; i < randuri; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void free_matrix(float **matrix, int randuri)
{
    int i;
    for (i = 0; i < randuri; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void allocate_d_matrix(int **matrix, int randuri, int coloane)
{
    int i;
    for (i = 0; i < randuri; i++)
    {
        matrix[i] = (int *)malloc(coloane * sizeof(int));
    }
}


void allocate_f_matrix(float **matrix, int randuri, int coloane)
{
    int i;
    for (i = 0; i < randuri; i++)
    {
        matrix[i] = (float *)malloc(coloane * sizeof(int));
    }
}

void init_d_matrix(int **matrix, int rows, int columns)
{
     int i, j = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            matrix[i][j] = -1;
        }
    }
}

void init_f_matrix(float **matrix, int rows, int columns)
{
     int i, j = 0;
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void tranpose_matrix(float **matrix, int **tr_matrix, int rows, int columns)
{
    int i,j=0;
    for(i=0;i<rows;i++)
    {
        for(j=0;j<columns;j++)
        {
            tr_matrix[i][j]=matrix[j][i];
        }
    }
}