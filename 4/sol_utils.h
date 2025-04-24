#ifndef SOL_UTILS_H
#define SOL_UTILS_H


int check_memory(struct info* inf);
int check_memory_c(char* inf);
int check_natural(int a);
struct info* menu(struct info* inf);
struct info* add_struct(struct info* inf, int col);
void cost_enter(char* date);
void disp_info(struct info* inf, int n);
void cost_search(struct info* inf, int n);
struct info* remove_by_name(struct info* inf, int* n);
void safe_input_int(int* var);
void flush();
int enter_str(char** str);
void division_count();

struct name
{
    char name[11];
    int players_amount;
};
struct info
{
    int cost;
    char* genre;
    struct name n;
};

#endif#pragma once
