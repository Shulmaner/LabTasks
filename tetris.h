#ifndef TETRIS_H
#define TETRIS_H

#define ROWS 20
#define COLS 12
#define BUFFER_SIZE (ROWS * (COLS * 2 + 1) + 1) // Каждая ячейка: символ+пробел, +1 для '\n' в конце строки

// Глобальный буфер экрана
char screen_buffer[BUFFER_SIZE];

typedef struct {
    int shape[4][4];
    int width;  // Ширина фигуры (для оптимизации)
    int height; // Высота фигуры
} Tetrimino;

extern Tetrimino tetriminos[7];
Tetrimino fig_rand();
void print_tetrimino(Tetrimino t);
void motion_upd(int** array);
void field_print(int** array);
void init_buffer();
#endif