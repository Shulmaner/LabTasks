#ifndef TETRIS_H
#define TETRIS_H

#define ROWS 20
#define COLS 12
#define BUFFER_SIZE (ROWS * (COLS * 2 + 1) + 1) // ������ ������: ������+������, +1 ��� '\n' � ����� ������

// ���������� ����� ������
char screen_buffer[BUFFER_SIZE];

typedef struct {
    int shape[4][4];
    int width;  // ������ ������ (��� �����������)
    int height; // ������ ������
} Tetrimino;

extern Tetrimino tetriminos[7];
Tetrimino fig_rand();
void print_tetrimino(Tetrimino t);
void motion_upd(int** array);
void field_print(int** array);
void init_buffer();
#endif