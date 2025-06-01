#include "tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

Tetrimino tetriminos[7] = {
    {.shape = {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, .width = 4, .height = 4 }, // I
    {.shape = {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {1,1,0,0}}, .width = 3, .height = 4 }, // J
    {.shape = {{0,0,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,1,0}}, .width = 3, .height = 4 }, // L
    {.shape = {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, .width = 2, .height = 2 }, // O
    {.shape = {{0,0,0,0}, {0,0,1,1}, {0,1,1,0}, {0,0,0,0}}, .width = 3, .height = 3 }, // S
    {.shape = {{0,0,0,0}, {0,1,1,1}, {0,0,1,0}, {0,0,0,0}}, .width = 3, .height = 3 }, // T
    {.shape = {{0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0}}, .width = 3, .height = 3 }  // Z
};

Tetrimino fig_rand() {
    static Tetrimino bag[7];
    static int index = 7;

    if (index >= 7) {
        for (int i = 0; i < 7; i++) {
            bag[i] = tetriminos[i];
        }

        for (int i = 6; i > 0; i--) {
            int j = rand() % (i + 1);
            Tetrimino temp = bag[i];
            bag[i] = bag[j];
            bag[j] = temp;
        }
        index = 0;
    }

    return bag[index++];
}

void print_tetrimino(Tetrimino t) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (t.shape[i][j] == 1) {
                printf("# "); // Блок
            }
            else {
                printf("  "); // Пусто
            }
        }
        printf("\n");
    }
}

void init_buffer() {
    // Заполняем буфер пробелами и переводами строк
    int pos = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            screen_buffer[pos++] = ' ';
            screen_buffer[pos++] = ' ';
        }
        screen_buffer[pos++] = '\n';
    }
    screen_buffer[pos] = '\0';
}

void add_figure_to_matrix(int** array, Tetrimino figure) {
    // Позиция вверху посередине
    int start_x = (COLS - figure.width) / 2;
    int start_y = -1;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (figure.shape[i][j]) {
                if (start_y + i < ROWS && start_x + j >= 0 && start_x + j < COLS) {
                    array[start_y + i][start_x + j] = 1;
                }
            }
        }
    }
}

void field_print(int** array) {
    // Обновляем только измененные символы в буфере
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int pos = i * (COLS * 2 + 1) + j * 2;
            screen_buffer[pos] = array[i][j] ? '#' : ' ';
        }
    }

    // Быстрый вывод с очисткой экрана
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { 0, 0 };
    SetConsoleCursorPosition(hConsole, pos);
    printf("%s", screen_buffer);
}

bool is_moving_pieces_present(int** array) {
    for (int i = 0; i < ROWS - 1; i++) {
        for (int j = 1; j < COLS - 1; j++) {
            if (array[i][j] == 1) { // 1 - движущаяся фигура
                return true;
            }
        }
    }
    return false;
}

void motion_upd(int** array) {
    static Tetrimino current;
    static bool figure_active = false;
    static bool need_new_figure = false;

    if (!figure_active || need_new_figure) {
        current = fig_rand();
        add_figure_to_matrix(array, current);
        figure_active = true;
        need_new_figure = false;
        return;
    }

    // Проверяем, может ли вся фигура двигаться вниз
    bool can_move_down = true;
    for (int i = ROWS - 2; i >= 0; i--) {
        for (int j = COLS - 2; j >= 1; j--) {
            if (array[i][j] == 1) { // Если это часть текущей фигуры
                if (array[i + 1][j] == 2 || i + 1 == ROWS - 1) {
                    can_move_down = false;
                    break;
                }
            }
        }
        if (!can_move_down) break;
    }

    // Если можно двигаться вниз - перемещаем всю фигуру
    if (can_move_down) {

        for (int i = ROWS - 2; i >= 0; i--) {
            for (int j = COLS - 2; j >= 1; j--) {
                if (array[i][j] == 1) {
                    array[i][j] = 0;
                    array[i + 1][j] = 1;
                }
            }
        }
    }
    else {
        // Фиксируем всю фигуру
        for (int i = ROWS - 2; i >= 0; i--) {
            for (int j = COLS - 2; j >= 1; j--) {
                if (array[i][j] == 1) {
                    array[i][j] = 2;
                }
            }
        }
        for (int i = ROWS - 2; i >= 0; i--) {
            bool row_full = true;

            // Проверяем, заполнена ли строка (игнорируя границы)
            for (int j = 1; j < COLS - 1; j++) {
                if (array[i][j] != 2) {
                    row_full = false;
                    break;
                }
            }

            // 2. Если строка заполнена - удаляем её
            if (row_full) {
                // Сдвигаем все вышестоящие строки вниз
                for (int k = i; k > 0; k--) {
                    for (int j = 1; j < COLS - 1; j++) {
                        array[k][j] = array[k - 1][j];
                    }
                }

                // Очищаем самую верхнюю строку (кроме границ)
                for (int j = 1; j < COLS - 1; j++) {
                    array[0][j] = 0;
                }

                // После сдвига проверяем эту же позицию снова
                i++;
            }
        }
        figure_active = false;
        need_new_figure = true;
    }
}

