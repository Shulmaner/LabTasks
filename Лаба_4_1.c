#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ROWS 10
#define COLUMNS 12

void saddle(int arr[ROWS][COLUMNS], int i, int j, bool* flag);

int main() {
    srand(time(NULL));
    int arr[ROWS][COLUMNS];
    int choose;
    bool flag = false;
    int isCorrect;
    printf("If you want to fill the array by yourself, print 1\nIf you want a random array, print 2\nMake a choice: ");
    scanf_s("%d", &choose);
    switch (choose) {
    case 1:
        printf("Input the matrix elements:\n");
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                isCorrect = scanf_s("%d", &arr[i][j]);
                if (isCorrect == 0)
                {
                    break;
                }
            }
            if (isCorrect == 0)
            {
                printf("Error");
                break;
            }
        }
        if (isCorrect != 0)
        {
            for (int i = 0; i < ROWS; i++)
            {
                for (int j = 0; j < COLUMNS; j++)
                {
                    saddle(arr, i, j, &flag);
                }
            }
            if (flag == false) { printf("There are no saddle numbers"); }
        }
        break;
    case 2:
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                arr[i][j] = 30 - rand() % 61;
                printf("%3d ", arr[i][j]);
            }
            printf("\n");
        }
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                saddle(arr, i, j, &flag);
            }
        }
        if (flag == false) { printf("There are no saddle numbers"); }
        break;
    default:
        printf("You've put an incorrect value, ERROR\n");
    }
    return 0;
}
void saddle(int arr[ROWS][COLUMNS], int i, int j, bool* flag) {
    int minrow = 1, maxrow = 1, mincol = 1, maxcol = 1;
    for (int k = 0; k < COLUMNS; k++) {
        if (arr[i][k] < arr[i][j]) {
            minrow = 0;
        }
        if (arr[i][k] > arr[i][j]) {
            maxrow = 0;
        }
    }
    for (int k = 0; k < ROWS; k++) {
        if (arr[k][j] > arr[i][j]) {
            maxcol = 0;
        }
        if (arr[k][j] < arr[i][j]) {
            mincol = 0;
        }
    }
    if ((minrow && maxcol) || (maxrow && mincol)) {
        *flag = true;
        printf("Saddle point: \n[%d][%d](value: %d)\n", i, j, arr[i][j]);
    }
}

/*
0 1 2 3 4 5 6 7 8 9 10 11
11 10 9 8 7 6 5 4 3 2 1 12
10 11 12 5 6 8 9 5 6 2 3 13
45 5 98 6 2 5 6 78 98 32 12 36
48 9 5 6 2 56 89 56 4 59 78 65
7862 98 6 8 8 8 7 9 5 6 3 125
45 78 96 25 35 64 8 78 95 58 58 58
45 89 65 89 87 96 56 58 45 25 25 25
48 58 98 6 5 47 85 98 32 59 59 59
78 45 89 23 45 12 89 59 89 63 63 63
*/

/*
11 12 13 14 15 16 17 18 19 20 21 22
10 12 20 30 50 40 100 120 360 560 40 74
9 4545 25947 145 5 56 9 8 4 2 65 9
8 1 2 3 4 5 6 7 8 9 10 20
7 80 50 230 10 89 40 8 65 230 20 10
6 80 50 230 10 89 40 8 65 230 20 10
5 80 50 230 10 89 40 8 65 230 20 10
4 80 50 230 10 89 40 8 65 230 20 10
3 80 50 230 10 89 40 8 65 230 20 10
2 1 1 1 1 1 1 1 1 1 1 1
*/