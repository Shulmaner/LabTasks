/*В квадратной матрице размером NxN найти сумму элементов в 2-ой области*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100  

int safe_input_int();
int main() {
    srand(time(NULL));
    int n;
    int array[MAX_SIZE][MAX_SIZE];
    int sum_num = 0;
    int input_method = 0;

    printf("Enter number of array elements x^2 (min 3, max 100): ");
    n = safe_input_int();
    while (n < 3 || n > MAX_SIZE) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        n = safe_input_int();
    }

    printf("Print 1 if you want to write array yourself, print 2 if you want a random array: ");
    input_method = safe_input_int();
    while (input_method != 1 && input_method != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        input_method = safe_input_int();
    }

    if (input_method == 1) {
        printf("Define an array: \n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                array[i][j] = safe_input_int_space();
                if (n % 2 == 0)
                {
                    if (j > i && i + j > n - 1)
                    {
                        sum_num += array[i][j];
                    }
                }
                if (n % 2 != 0)
                {
                    if (j > i && i + j > n - 1)
                    {
                        sum_num += array[i][j];
                    }
                }
            }
        }
        printf("The sum of elements in area two: %d", sum_num);
        printf("\n");
    }
    else
    {
        if (input_method == 2) 
        {
            printf("Defined array: \n");
            for (int i = 0; i < n; i++) 
            {

                for (int j = 0; j < n; j++) 
                {
                    array[i][j] = 10 - rand() % 21;
                    printf("%4d", array[i][j]);
                    if (n%2 == 0)
                    {
                        if (j>i && i+j>n-1)
                        {
                            sum_num += array[i][j];
                        }
                    }
                    if (n%2 != 0)
                    {
                        if (j>i && i+j>n-1)
                        {
                            sum_num += array[i][j];
                        }
                    }
                    
                }
                printf("\n");
            }
            printf("\n");
            printf("The sum of elements in area two: %d", sum_num);
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
        if ((c = getchar()) != '\n' && c != EOF) {
            printf("Incorrect input, rest of the line is discarded, try again: ");
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else
            return var;
    }
}

int safe_input_int_space() {
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