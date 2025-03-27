#include <stdio.h>
#include <stdlib.h>

void selectionSortNeg(char* filename, int count_number);
void swap(FILE* file, int i, int j);
int solution(int argc, char* argv[]);
int safe_input_int(int* exitFlag);
void flush();

int main(int argc, char* argv[]) {
    return solution(argc, argv);
}

int solution(int argc, char* argv[]) {

    const char* filename = argv[1];
    FILE* file;
    if (fopen_s(&file, filename, "wb+") != 0) {
        printf("Error opening file for writing");
        return 1;
    }

    if (argc >= 2) {
        printf("To complete the entry, write q\n");
    }
    if (!file) {
        printf("FILE = NULL_PTR");
        return 1;
    }

    int flag = 0, total_weight = 0, count_number = 0;
    int num, capacity;
    printf("Enter the payload capacity of the vehicle: ");
    scanf_s("%d", &capacity);
    while (1) {
        if (!flag) {
            num = safe_input_int(&flag); //ввод веса груза
            if (num <= 0) {
                continue;
            }
            count_number++;
            total_weight += num;
            if (total_weight > capacity) {  //подсчет итогового веса груза
                total_weight -= num;
                count_number--;
            }
            fwrite(&num, sizeof(int), 1, file);
        }
        else {
            break;
        }
    }

    fclose(file); // Закрываем файл после записи данных

    selectionSortNeg(filename, count_number);

    printf("\nYou can take away %d item(s)\n", count_number); //вывод переменных
    printf("Total weight taken away %d\n", total_weight);

    if (fopen_s(&file, filename, "rb") != 0) { // Открываем файл заново для чтения отсортированных данных
        printf("Error opening file for reading");
        return 1;
    }

    printf("Sorted file contents: ");
    while (fread(&num, sizeof(int), 1, file)) {
        printf("%d ", num);
    }

    fclose(file);
    return 0;
}

void selectionSortNeg(char* filename, int count_number)
{
    FILE* file;
    if (fopen_s(&file, filename, "rb+") != 0) {
        printf("Error opening file for reading and writing");
        return;
    }

    for (int i = 0; i < count_number; i++) {
        int minValue, index_min = i, num;
        fseek(file, i * sizeof(int), SEEK_SET);
        fread(&minValue, sizeof(int), 1, file);
        for (int j = i + 1; j < count_number; j++) {
            fseek(file, j * sizeof(int), SEEK_SET);
            fread(&num, sizeof(int), 1, file);
            if (num < minValue) {
                minValue = num;
                index_min = j;
            }
        }
        swap(file, i, index_min);
    }

    fclose(file);
}

void swap(FILE* file, int i, int j)
{
    if (i == j) return;
    int num1, num2;
    fseek(file, i * sizeof(int), SEEK_SET);
    fread(&num1, sizeof(int), 1, file);

    fseek(file, j * sizeof(int), SEEK_SET);
    fread(&num2, sizeof(int), 1, file);

    fseek(file, i * sizeof(int), SEEK_SET);
    fwrite(&num2, sizeof(int), 1, file);

    fseek(file, j * sizeof(int), SEEK_SET);
    fwrite(&num1, sizeof(int), 1, file);
}

int safe_input_int(int* exitFlag)
{
    int var;
    int c;
    while (1)
    {
        while (scanf_s("%d", &var) != 1)
        {
            c = getchar();
            if (c == 'q')
            {
                *exitFlag = 1;
                flush();
                return 0;
            }
            printf("Incorrect input, rest of the line is discarded, try again\n");
            flush();
        }
        if ((c = getchar()) != '\n' && c != ' ')
        {
            printf("Incorrect input, rest of the line is discarded, try again\n");
            flush();
        }
        else
            return var;
    }
}

void flush()
{
    int c;
    while ((c = getchar()) != '\n');
}
