#include <stdio.h>
#include <time.h>
#include <malloc.h>

void solution1();
void solution2();
int safe_input_int(); //объ€вл€ем прототипы
void bubble_sort(int max_elem, int k, int* ptr, int n);
void shell_sort(int* ptr, int n);

int main(void) {
    int solution_task = 0;
    printf("Choose what task do you need (1-2) ");
    solution_task = safe_input_int();
    while (solution_task != 1 && solution_task != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        solution_task = safe_input_int();
    }
    if (solution_task == 1) {
        solution1();
    }
    if (solution_task == 2) {
        solution2();
    }
    return 0;
}

void solution1() {
    srand(time(NULL));
    int k, n;
    int input_method = 0;
    int max_elem = 0;

    printf("Enter the number of elements of the array ");
    n = safe_input_int();
    int* ptr = malloc(n * sizeof(int));
    printf("Enter k, after a number divisible by k it will be sorted ");
    k = safe_input_int();
    
    printf("Print 1 if you want to write array yourself, print 2 if you want a random array: ");
    input_method = safe_input_int();
    while (input_method != 1 && input_method != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        input_method = safe_input_int();
    }

    switch (input_method)
    {
    case 1:
    {
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {
            printf("Defined array: \n");
            for (int i = 0; i < n; i++) {
                ptr[i] = safe_input_int();
                if (ptr[i] > ptr[max_elem]) {
                    max_elem = i;
                }
            }
            printf("Max element: %d\n", max_elem);
            bubble_sort(max_elem, k, ptr, n);

            printf("Changed array: \n");
            for (int i = 0; i < n; ++i) {
                printf("%d  ", ptr[i]);
            }
            free(ptr);
        }
        break;
    }
    case 2:
    {
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {

            printf("Defined array: \n");
            for (int i = 0; i < n; i++) {
                ptr[i] = rand() % 100;
                printf("%4d", ptr[i]);
                if (ptr[i] > ptr[max_elem]) {
                    max_elem = i;
                }
            }
            printf("\n");
            printf("Index of max element: %d\n", max_elem);

            bubble_sort(max_elem, k, ptr, n);

            printf("Changed array: \n");
            for (int i = 0; i < n; ++i) {
                printf("%4d", ptr[i]);
            }
            free(ptr);
        }
        break;
    }
    }
}

void bubble_sort(int max_elem,int k, int* ptr ,int n ) {
    for (int i = max_elem + 1; i < n; ++i)
    {
        if (ptr[i] % k == 0) {
            for (int j = i; j < n; ++j) {
                if (ptr[j] % k == 0 && ptr[i] > ptr[j]) {
                    int temp = ptr[i];
                    ptr[i] = ptr[j];
                    ptr[j] = temp;
                }
            }
        }
    }
}

void shell_sort(int* ptr, int n1, int n2) {
    for (int interval = n1 / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n1; i += 1) {
            int temp = ptr[i];
            int j;
            for (j = i; j >= interval && ptr[j - interval] > temp; j -= interval) {
                ptr[j] = ptr[j - interval];
            }
            ptr[j] = temp;
        }
    }
}

void solution2() {
    srand(time(NULL));
    int n1, n2;
    int input_method = 0;

    printf("Enter the number of elements of the array (x | y): ");
    n1 = safe_input_int();
    n2 = safe_input_int();

    int* ptr = malloc(n1 * n2 * sizeof(int));

    printf("Print 1 if you want to write array yourself, print 2 if you want a random array: ");
    input_method = safe_input_int();
    while (input_method != 1 && input_method != 2) {
        printf("Incorrectly entered data, please rewrite in normal way: ");
        input_method = safe_input_int();
    }

    switch (input_method)
    {
    case 1:
    {
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {
            printf("Defined array: \n");
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++) {
                    ptr[i * n2 + j] = safe_input_int();
                }
            }

            shell_sort(ptr, n1, n2);

            printf("Changed array: \n");
            for (int i = 0; i < n1; ++i) {
                for (int j = 0; j < n2; j++) {
                    printf("%d  ", ptr[i*n2 + j]);
                }
            }
            free(ptr);
        }
        break;
    }
    case 2:
    {
        if (ptr == NULL) {
            printf("Memory not allocated.\n");
        }
        else
        {

            printf("Defined array: \n");
            for (int i = 0; i < n1; i++) {
                for (int j = 0; j < n2; j++) {
                    ptr[i * n2 + j] = rand() % 100;
                    printf("%4d", ptr[i * n2 + j]);
                }
                printf("\n");
            }
            printf("\n");

            shell_sort(ptr, n1, n2);

            printf("Changed array: \n");
            for (int i = 0; i < n1; ++i) {
                for (int j = 0; j < n2; j++) {
                    printf("%4d", ptr[i * n2 + j]);
                }
                printf("\n");
            }
            free(ptr);
        }
        break;
    }
    }
}

int safe_input_int() {
    int var;
    int c, b, a = 0;
    while (1)
    {
        b = scanf_s("%d", &var);
        a = var;
        if (b != 1) {
            printf("Incorrect input, rest of the line is discarded, try again: ");
            while (getchar() != '\n');
        }
        if (a == -1) {
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