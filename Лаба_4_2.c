/*Найти в матрице первую строку, все элементы которой отрицательны. Увеличить все
элементы матрицы на значение первого элемента найденной строки*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100  

int safe_input_int();
int main() {
    srand(time(NULL));
    int n1,n2;
    int array[MAX_SIZE][MAX_SIZE];
    int neg_matr_count = 0;
    int sum_num = 0;
    int input_method = 0;

    printf("Enter number of array elements x | y (max 100*100): ");
    n1 = safe_input_int();
    n2 = safe_input_int();
    while (n1 <= 0 || n1 > MAX_SIZE || n2 <= 0 || n2 > MAX_SIZE) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        n1 = safe_input_int();
        n2 = safe_input_int();
    }

    printf("Print 1 if you want to write array yourself, print 2 if you want a random array: ");
    input_method = safe_input_int();
    while (input_method != 1 && input_method != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        input_method = safe_input_int();
    }

    if (input_method == 1) {
        printf("Define an array: \n");
        for (int i = 0; i < n1; i++)
        {
            for (int j = 0; j < n2; j++)
            {
                array[i][j] = safe_input_int();
            }
        }
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {     
                if (array[i][j] < 0) {
                    neg_matr_count++;
                }
                if (sum_num == 0) {
                    if (neg_matr_count == n2) {
                        sum_num = array[i][j - n2 + 1];
                    }
                }
                
            }
            neg_matr_count = 0;
            printf("\n");
        }
        printf("Changed array: \n");
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                array[i][j] += sum_num;
                printf("%4d ", array[i][j]);

            }
            printf("\n");
        }
        printf("\n");
    }  
    else 
    {
        if (input_method == 2) {
            printf("Defined array: \n");
            for (int i = 0; i < n1; i++) {
                
                for (int j = 0; j < n2; j++) {
                    array[i][j] = 10 - rand() % 21;
                    
                    if (array[i][j] < 0) {
                        neg_matr_count++;
                    }   
                    printf("%4d",array[i][j]);
                    if (sum_num == 0) {
                        if (neg_matr_count == n2) {
                            sum_num = array[i][j - n2 + 1];
                        }
                    }
                }
                neg_matr_count = 0;
                printf("\n");
            }
            printf("\n");
            printf("Changed array: \n");
            
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++) {
                    array[i][j] += sum_num;
                    printf("%4d", array[i][j]);

                }
                printf("\n");
            }
        }
    }
    return 0;
}

int safe_input_int() {
    int var;
    int c;
    while (1)
    {
        while (scanf_s("%d", &var) != 1) {
            printf("Incorrect input, rest of the line is discarded, try again: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        if ((c = getchar()) != '\n' && c != EOF && c != ' ') {
            printf("Incorrect input, rest of the line is discarded, try again: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else
            return var;
    }
}

