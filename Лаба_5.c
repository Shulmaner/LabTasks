#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define ARR_MAX 100
#define ARR_MAX_SOLV1 1000

void solution1(int limit);
void solution2();
void solution3();
int safe_input_int();
int safe_input_int();
int main(void) {
    int limit = 1000;
    int solution_task = 0;
    printf("Choose what task do you need (1-3) ");
    solution_task = safe_input_int();
    while (solution_task != 1 && solution_task != 2 && solution_task != 3) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        solution_task = safe_input_int();
    }

    if (solution_task == 1) {
        solution1(limit);
    }

    if (solution_task == 2) {
        solution2();
    }

    if (solution_task == 3) {
        solution3();
    }

    return 0;
}

void solution1(int limit) {
    bool isPrime[ARR_MAX_SOLV1 + 1];  

    for (int i = 0; i <= limit; i++) {
        isPrime[i] = true;
    }

    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {  
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }

    printf("Prime numbers up to %d:\n", limit);
    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            printf(" %d ", i);
            printf("\n");
        }
    }
    printf("\n");
}

void solution2() {
    srand(time(NULL));
    int input_method = 0;
    int n1, n2;

    printf("Enter number of array elements x | y (max 100*100): ");
    n1 = safe_input_int();
    n2 = safe_input_int();
    while (n1 <= 0 || n1 > ARR_MAX || n2 <= 0 || n2 > ARR_MAX) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        n1 = safe_input_int();
        n2 = safe_input_int();
    }
    int* ptr = malloc((n1 * n2) * sizeof(int));

    printf("Print 1 if you want to write array yourself, print 2 if you want a random array: ");
    input_method = safe_input_int();
    while (input_method != 1 && input_method != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        input_method = safe_input_int();
    }

    switch (input_method)
    {
    case 1:
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {
            printf("Defined array: \n");
            for (int i = 0; i < n1 * n2; i++) {
                ptr[i] = safe_input_int();
            }

            if (ptr == NULL) {
                printf("Memory not allocated.\n");
            }
            else
            {
                printf("Modified array: \n");
                for (int i = 0; i < n1; i++) {
                    for (int j = 0; j < n2; j++) {
                        if (ptr[i * n2 + j] == 0) {
                            printf("     ");
                        }
                        else
                            printf("%4d ", ptr[i * n2 + j]);
                    }
                    printf("\n");
                }
            }
            free(ptr);
        }
        break;
    case 2:
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {
            for (int i = 0; i < n1 * n2; i++)
                ptr[i] = rand() % 101;

            printf("Defined array: \n");
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++)
                    printf("%4d ", ptr[i * n2 + j]);
                printf("\n");
            }

            printf("Modified array: \n");
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++) {
                    if (ptr[i * n2 + j] == 0) {
                        printf("     ");
                    }
                    else
                        printf("%4d ", ptr[i * n2 + j]);
                }
                printf("\n");
            }
            free(ptr);
        }
        break;
    }
}

void solution3() {
    srand(time(NULL));
    int n1, n2;
    int sum = 0;
    int shift = 0;
    int input_method = 0;

    printf("Enter number of array elements x | y (min 3*3)(max 100*100): ");
    n1 = safe_input_int();
    n2 = safe_input_int();
    while (n1 < 3 || n1 > ARR_MAX || n2 < 3 || n2 > ARR_MAX) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        n1 = safe_input_int();
        n2 = safe_input_int();
    }
    int* ptr = malloc((n1 * n2) * sizeof(int));

    printf("Print 1 if you want to write array yourself, print 2 if you want a random array: ");
    input_method = safe_input_int();
    while (input_method != 1 && input_method != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        input_method = safe_input_int();
    }

    switch (input_method)
    {
    case 1:
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {
            printf("Defined array: \n");
            for (int i = 0; i < n1 * n2; i++) {
                ptr[i] = safe_input_int();
            }

            if (ptr == NULL) {
                printf("Memory not allocated.\n");
            } else
                for (int i = 0; i < n1; i++) {
                    for (int j = 0; j < n2; j++)
                        if (j > i) {
                            sum += ptr[i];
                        }
                }

            printf("The sum of elements above the diagonal: %d", sum);

            free(ptr);
        }
        break;
    case 2:
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {
            for (int i = 0; i < n1 * n2; i++)
                ptr[i] = rand() % 100;

            printf("Defined array: \n");
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++)
                    printf("%4d ", ptr[i * n2 + j]);
                printf("\n");
            }

            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++)
                    if (j>i) {
                        sum += ptr[i*n2 + j];
                    }
            }

            printf("The sum of elements above the diagonal: %d", sum);

            free(ptr);
        }
        break;
    }
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