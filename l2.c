#include <stdio.h>
#include <conio.h>

int file_entry(int argc, char* argv[]);
void size_word_count();
void word_spacing();
int safe_input_int();

int main(int argc, char* argv[]) {
	file_entry(argc, argv);
	size_word_count();
	word_spacing();
	return 0;
}

int file_entry(int argc, char* argv[]) {
    FILE* file = fopen("output.txt", "w");
    if (argc >= 2) {
        printf("To complete the entry, write ',,'\n");
    }
    if (!file) {
        printf("FILE = NULL_PTR");
        return 1;
    }
        
    char first_comma, sec_comma = 0;                                           //запись первых символов в файл
    while ((first_comma = getchar()) != EOF) {
        fputc(first_comma, file);
        if (sec_comma == ',' && first_comma == ',') {
            fseek(file, -1, SEEK_CUR);
            fputc(' ', file);
            fflush(file);
            fseek(file, -2, SEEK_CUR);
            fputc(' ', file);
            fflush(file);
            break;
        }
        sec_comma = first_comma;
    }
    fclose(file);

    if (fopen_s(&file, "output.txt", "r") != 0) {
        printf("Error opening a file for reading!\n");
        return 1;
    }

    printf("\nFile contents:\n");
    int symb_read;
    while ((symb_read = fgetc(file)) != EOF) {                                  //вывод последующей записи в файле
        putchar(symb_read);
    }

    fclose(file);
    return 0;
}

void size_word_count() {
    int word_lenth, amount = 0;
    printf("\n\nEnter the length of the words to find: ");
    word_lenth = safe_input_int();
    if (word_lenth == 0) {
        printf("\nThe length cannot be 0, please rewrite the value: ");
        word_lenth = safe_input_int();
    }

    FILE* file = fopen("output.txt", "r");              
    if (!file) {
        printf("FILE = NULL_PTR");
    }

    int word_count = 0;                                                         //подсчет длины слова по заданной длине 
    char symb_read;
    while ((symb_read = fgetc(file)) != EOF) {
        word_count++;
        if (symb_read == ' ' || symb_read == '\n') {
            word_count--;
            if (word_count == word_lenth) {
                amount++;
            }
            word_count = 0;
        }    
    }

    printf("Total amount of words: %d\n\n", amount);
    fclose(file);
}

void word_spacing(){
    char setted_symbol;
    FILE* file = fopen("output.txt", "r+");
    if (!file) {
        printf("FILE = NULL_PTR");
    }

    printf("Enter the required symbol: ");
    setted_symbol = _getch();                                                     //запрашиваем символ 
    printf("%c", setted_symbol);                                                 
    while (setted_symbol == ' ' || setted_symbol == '\r') {
        printf("\nSymbol is incorrect, please try again: ");
        setted_symbol = _getch();
        printf("%c", setted_symbol);
    }

    int word_count = 0, inside_target_word = 0;
    long word_start_pos = -1;  
    char symb_read;

    while ((symb_read = fgetc(file)) != EOF) {
        if (symb_read == ' ' || symb_read == '\n') {                              //меняем слово на пробелы
            inside_target_word = 0; 
            word_start_pos = -1;
        }
        else {
            if (word_start_pos == -1) {
                word_start_pos = ftell(file) - 1;
                if (symb_read == setted_symbol) {
                    inside_target_word = 1;
                }
            }

            if (inside_target_word) { 
                fseek(file, -1, SEEK_CUR);
                fputc(' ', file);
                fflush(file);
            }
        }
    }
    fclose(file);

    if (fopen_s(&file, "output.txt", "r") != 0) {
        printf("Error opening a file for reading!\n");
        return;
    }

    printf("\nFile contents:\n");
    int symb_out;
    while ((symb_out = fgetc(file)) != EOF) {                                  //вывод итоговой записи в файле
        putchar(symb_out);
    }

    fclose(file);
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
            while ((c = getchar()) != '\n' && c != EOF);
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