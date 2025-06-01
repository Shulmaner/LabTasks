#include "tetris.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



int main() {
	int rows = 20, cols = 12;
	int speed = 300;
	bool flag = false;
	int** array = (int**)calloc(rows, sizeof(int*));
	for (int i = 0; i < rows; i++) {
		array[i] = (int*)calloc(cols, sizeof(int));
	}
	init_buffer();
	printf("TETRIS!										ple-alpha 1.0.0\n");
	printf("Press any button to continue...\n");
	_getch();
	system("cls");
	// ������ ���������� ������
	for (int i = 0; i < ROWS; i++) {
		array[i][0] = array[i][COLS - 1] = 2;
	}
	for (int j = 0; j < COLS; j++) {
		array[ROWS - 1][j] = 2;
	}

	while (1) {
		if (_kbhit()) {
			int key = _getch();
			int max_x = 12;
			int min_x = -1;
			switch (key) {
			case 'a': {  // �����
				// ������� ����������� X-��������� ������
				int min_x = COLS;
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						if (array[i][j] == 1 && j < min_x) {
							min_x = j;
						}
					}
				}

				// ���� ��� � ����� ������� ��� ���� ����������� - �� �������
				if (min_x == 0) break;

				// ��������� �������� �����
				bool can_move = true;
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						if (array[i][j] == 1 && array[i][j - 1] == 2) {
							can_move = false;
							break;
						}
					}
					if (!can_move) break;
				}

				// ������� ������
				if (can_move) {
					for (int j = 1; j < COLS; j++) {
						for (int i = 0; i < ROWS; i++) {
							if (array[i][j] == 1) {
								array[i][j - 1] = 1;
								array[i][j] = 0;
							}
						}
					}
				}
				break;
			}
			case 'd': {  // �������� ������
				// 1. ��������� ����������� ��������
				bool can_move = true;
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						if (array[i][j] == 1) {  // ���� ��� ����� ������
							if (j == COLS - 1 || array[i][j + 1] == 2) {  // ������� ��� �����������
								can_move = false;
								break;
							}
						}
					}
					if (!can_move) break;
				}

				// 2. ���� �������� �������� - ����������
				if (can_move) {
					// ������� ���������� ������� ������ �����, ����� �����
					for (int j = COLS - 2; j >= 0; j--) {
						for (int i = 0; i < ROWS; i++) {
							if (array[i][j] == 1) {
								array[i][j] = 0;    // ������� ������� �������
								array[i][j + 1] = 1;  // ������������� ����� �������
							}
						}
					}
				}
				break;
			}
			case 'w': {  // ������� ������
				// 1. ������� ��� ����� ������� ������ (�������� 1)
				int blocks[4][2]; // �������� 4 ����� � ������
				int block_count = 0;

				// �������� ���������� ���� ������ ������
				for (int i = 0; i < ROWS; i++) {
					for (int j = 0; j < COLS; j++) {
						if (array[i][j] == 1) {
							blocks[block_count][0] = i; // Y-����������
							blocks[block_count][1] = j; // X-����������
							block_count++;
						}
					}
				}
				if (block_count == 0) break;

				// 2. ��������� ����� �������� (������� ��������������)
				int center_y = 0, center_x = 0;
				for (int i = 0; i < block_count; i++) {
					center_y += blocks[i][0];
					center_x += blocks[i][1];
				}
				center_y /= block_count;
				center_x /= block_count;

				// 3. ��������� ����������� ��������
				bool can_rotate = true;
				for (int i = 0; i < block_count; i++) {
					// ��������� ����� ���������� ����� ��������
					int rel_y = blocks[i][0] - center_y;
					int rel_x = blocks[i][1] - center_x;
					int new_x = center_x - rel_y;
					int new_y = center_y + rel_x;

					// ��������� ������� � ��������
					if (new_x < 0 || new_x >= COLS || new_y >= ROWS ||
						(new_y >= 0 && array[new_y][new_x] == 2)) {
						can_rotate = false;
						break;
					}
				}

				// 4. ���� ������� �������� - ��������� ���
				if (can_rotate) {
					// ������� ������� ������� �����
					for (int i = 0; i < block_count; i++) {
						array[blocks[i][0]][blocks[i][1]] = 0;
					}

					// ����� ������ ���������� �����
					for (int i = 0; i < block_count; i++) {
						int rel_y = blocks[i][0] - center_y;
						int rel_x = blocks[i][1] - center_x;
						int new_x = center_x - rel_y;
						int new_y = center_y + rel_x;
						array[new_y][new_x] = 1;
					}
				}
				break;
			}
			}
				//case 'w': case 72: rotate_piece(); return;  // ������
		}
		motion_upd(array);
		field_print(array);
		Sleep(speed);

	}

	for (int i = 0; i < rows; i++) {
		free(array[i]);
	}
	free(array);
	return 0;
}