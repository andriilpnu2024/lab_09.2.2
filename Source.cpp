#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "var.h"

#define N 5
void matrixrowcols(const char* format, int& rows, int& cols);
void MatrixInput(const char* format, ...);

int main() 
{
    char input[100];
    printf("Input string: ");
    fgets(input, sizeof(input), stdin);
    MatrixInput(input,1,2,3,5,23,43);
    return 0;
}

void MatrixInput(const char* format, ...)
{
    int rows = 0, cols = 0;
    int firstdigit = 0;
    int firstalpha = 0;
    va_list arg;
    va_start(arg, format);

    matrixrowcols(format,rows,cols);

    if (rows == 0 || cols == 0) {
        printf("Expected digit or alphabetic symbol was not found!.\n");
        return;
    }

    printf("Matrix size: %d x %d\n", rows, cols);

    // Виділення пам'яті під матрицю
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    // Заповнення матриці значеннями з аргументів
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i * cols + j < strlen(format)) {
                char currentChar = format[i * cols + j];
                if (isdigit(currentChar)) {
                    matrix[i][j] = currentChar - '0';
                }
                else
                {
                    matrix[i][j] = 0;  // Non-digit characters are considered 0
                }
            }
            else 
            {
                matrix[i][j] = 0;  // If we run out of input string, fill the remaining cells with 0
            }
            printf("%d ", matrix[i][j]);  // Output the matrix value
        }
        printf("\n");
    }

    va_end(arg);

    // Звільнення пам'яті для матриці
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void matrixrowcols(const char* format, int& rows,int &cols)
{
    int firstdigit = 0;
    int firstalpha = 0;
    for (int i = 0; format[i] != '\0'; i++) {
        if (isdigit(format[i])) {
            if (firstdigit == 0) {
                rows = format[i] - '0';
                firstdigit = 1;
            }
        }
    }

    for (int i = 0; format[i] != '\0'; i++) {
        if (isalpha(format[i])) {
            if (firstalpha == 0) {
                cols = format[i] / N;  // Визначення стовпців через позицію літери
                firstalpha = 1;
            }
        }
    }
}



