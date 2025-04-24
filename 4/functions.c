#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "sol_utils.h"



int check_memory(struct info* inf)
{
    if (inf == NULL)
    {
        printf("Error: couldn't allocate memory\n");
        exit(0);
    }
    return 0;
}

int check_memory_c(char* inf)
{
    if (inf == NULL)
    {
        printf("Error: couldn't allocate memory\n");
        exit(0);
    }
    return 0;
}

int check_natural(int a)
{
    if (a <= 0)
    {
        printf("Error: the number does not match the condition\n");
        return 1;
    }
    return 0;
}

struct info* menu(struct info* inf)
{
    int counter = 0;
    while (1)
    {
        printf("Menu:\n1 - add a game\n2 - view all games\n");
        printf("3 - find the game by cost\n4 - delete a game\n5 - fine the reminder of the division\n6 - exit\n\n");
        char c = _getch();
        switch (c)
        {
        case '1':
            counter++;
            inf = add_struct(inf, counter);
            break;
        case '2':
            disp_info(inf, counter);
            break;
        case '3':
            cost_search(inf, counter);
            break;
        case '4':
            inf = remove_by_name(inf, &counter);
            break;
        case '5':
            division_count();
            break;
        case '6':
            for (int i = 0; i < counter; i++)
            {
                free(inf[i].genre);
            }
            return inf;
        default:
            printf("Incorrect input, try again\n");
        }
        printf("\n");
    }
}

struct info* add_struct(struct info* inf, int col)
{
    struct info* i = (struct info*)realloc(inf, sizeof(struct info) * col);
    check_memory(i);

    cost_enter(&(i[col - 1].n.name[0]));
    printf("Enter the genre of a game:\n");
    i[col - 1].genre = (char*)malloc(sizeof(char));
    check_memory_c(i[col - 1].genre);
    enter_str(&(i[col - 1].genre));

    printf("Enter the cost of a game:\n");
    do
    {
        safe_input_int(&(i[col - 1].cost));
    } while (check_natural(i[col - 1].cost));

    printf("Enter the maximum of players:\n");
    do
    {
        safe_input_int(&(i[col - 1].n.players_amount));
    } while (check_natural(i[col - 1].n.players_amount));
    return i;
}

void cost_enter(char* name)
{
    while (1)
    {
        printf("Enter the game name:\n");
        int i = 0;
        char c;
        while ((c = getchar()) != '\n' && c != EOF && i < 99)
        {
            name[i++] = c;
        }
        name[i] = '\0';
        if (i > 0)
        {
            return;
        }

        printf("Error: Name cannot be empty\n");
    }
}

void disp_info(struct info* inf, int n)
{
    if (n == 0)
        printf("The list is empty.\n");
    for (int i = 0; i < n; i++)
    {
        printf("Name of a game: %s\n", &(inf[i].n.name[0]));
        printf("Genre of the game: %s\n", inf[i].genre);
        printf("Cost of the game: %d\n", inf[i].cost);
        printf("Maximum of a players: %d \n\n", inf[i].n.players_amount);
    }
}

void cost_search(struct info* inf, int n)
{
    int desired_cost = 0;
    printf("Enter the cost of a game: ");
    safe_input_int(&desired_cost); 

    printf("The game(s) of desired price:\n");
    int found = 0;  

    for (int i = 0; i < n; i++)  
    {
        if (inf[i].cost == desired_cost)  
        {
            printf("Name of the game: %s\n", inf[i].n.name);
            found = 1;  
        }
    }

    if (!found) {
        printf("No games found with the specified price.\n");
    }
}

struct info* remove_by_name(struct info* inf, int* n)
{
    char c[11];
    struct info* in = (struct info*)realloc(inf, sizeof(struct info) * (*n));
    check_memory(in);
    cost_enter(c);
    int flag = 0;
    for (int i = 0; i < (*n); i++)
    {
        if (strcmp(c, &(inf[i].n.name[0])) == 0)
        {
            flag = 1;
            inf[i] = inf[(*n) - 1];
            (*n)--;
            in = (struct info*)realloc(in, sizeof(struct info) * (*n));
        }
    }
    if (flag == 0)
        printf("The specified date was not found\n");
    return in;
}

void safe_input_int(int* var)
{
    int c;
    while (1)
    {
        while (scanf_s("%d", var) != 1)
        {
            printf("Incorrect input, rest of the line is discarded, try again\n");
            flush();
        }
        if ((c = getchar()) != '\n' && c != ' ')
        {
            printf("Incorrect input, rest of the line is discarded, try again\n");
            flush();
        }
        else return;
    }
}

void flush()
{
    int c;
    while ((c = getchar()) != '\n');
}

int enter_str(char** str)
{
    do
    {
        int pos = 0;
        char c;
        do
        {
            c = getchar();
            *str = (char*)realloc(*str, sizeof(char) * (pos + 1));
            check_memory_c(str);
            if (c == '\n')
            {
                (*str)[pos] = '\0';
                break;
            }
            (*str)[pos] = c;
            pos++;
        } while (c != '\n');
        if ((*str)[0] == '\0') printf("An empty line. Please try again.\n");
    } while ((*str)[0] == '\0');
    return 0;
}

void division_count() {
    int number;
    printf("Enter an integer: ");
    safe_input_int(&number);
    struct bit_read_end { int remainder : 3; };
    struct bit_read_end result;
    result.remainder = number;
    printf("Remainder of division %u by 8: %u\n", number, result.remainder);
}