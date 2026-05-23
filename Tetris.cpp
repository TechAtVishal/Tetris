#include <iostream>
#include <string>
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int score = 0;
int main_grid[51][61];

void PreGameRun() {
	int i, j;
	for (i = 1; i <= 50; i++) {
		for (j = 1; j <= 60; j++) {
			if (j < 20 || j >= 40 || i >= 40)
				main_grid[i][j] = 10;
			if (i == 40)
				main_grid[i][j] = 5;
		}
	}
}

void DrawMainGUI() {
	DrawRectangle(0, 0, 600, 500, BLACK);
	DrawRectangle(0, 0, 200, 500, BLUE);
	DrawRectangle(400, 0, 200, 500, BLUE);
	DrawRectangle(0, 0, 600, 100, BLUE);
	DrawRectangle(0, 400, 600, 100, BLUE);
	DrawText(TextFormat("NEXT"), 65, 200, 20, BLACK);
	DrawRectangle(65, 225, 65, 65, PURPLE);
	DrawText(TextFormat("SCORE:  %03i", score), 450, 200, 20, BLACK);
	DrawText(TextFormat("TETRIS"), 220, 20, 40, BLACK);
}

void PieceGen(int piece_choice) {
	int x = 28, y = 5;
	if (piece_choice == 0)
		main_grid[y][x] = main_grid[y][x + 1] = main_grid[y + 1][x] = main_grid[y + 1][x + 1] = 1;	//sqaure;
	if (piece_choice == 1)
		main_grid[y][x] = main_grid[y + 1][x] = main_grid[y + 2][x] = main_grid[y + 2][x - 1] = 1;	//reverse L;
	if (piece_choice == 2)
		main_grid[y][x] = main_grid[y + 1][x] = main_grid[y + 2][x] = main_grid[y + 2][x + 1] = 1;	//L;
	if (piece_choice == 3)
		main_grid[y][x] = main_grid[y + 1][x] = main_grid[y + 2][x] = main_grid[y + 3][x] = 1;	//straight line;
	if (piece_choice == 4)
		main_grid[y][x] = main_grid[y][x + 1] = main_grid[y + 1][x + 1] = main_grid[y + 1][x + 2] = 1;	//z;
	if (piece_choice == 5)
		main_grid[y][x] = main_grid[y][x + 1] = main_grid[y + 1][x] = main_grid[y + 1][x - 1] = 1;	//reverse z;
	if (piece_choice == 6)
		main_grid[y][x] = main_grid[y + 1][x - 1] = main_grid[y + 1][x] = main_grid[y + 1][x + 1] = 1;	//reverse t;
}

bool is_Obstacle(int y, int x) {
	if (main_grid[y][x] == 2 || main_grid[y][x] == 10)
		return true;
	return false;
}

void PiecePlayerMovement() {
	int i, j;
	bool flag = true;
	if (IsKeyDown(KEY_A)) {
		for (j = 20; j < 40; j++) {
			for (i = 0; i < 40; i++) {
				if (main_grid[i][j] == 1) {
					if (is_Obstacle(i, j-1))
					{
						flag = false;
						break;
					}
				}
			}
			if (!flag)
				break;
		}
		if (flag) {
			for (j = 20; j < 40; j++) {
				for (i = 0; i < 40; i++) {
					if (main_grid[i][j] == 1) {
						main_grid[i][j - 1] = 1;
						main_grid[i][j] = 0;
					}
				}
			}
		}
	}
	flag = true;
	if (IsKeyDown(KEY_D)) {
		for (j = 39; j >= 20; j--) {
			for (i = 0; i <= 40; i++) {
				if (main_grid[i][j] == 1) {
					if (is_Obstacle(i, j+1))
					{
						flag = false;
						break;
					}
				}
			}
			if (!flag)
				break;
		}
		if (flag) {
			for (j = 39; j >= 20; j--) {
				for (i = 0; i <= 40; i++) {
					if (main_grid[i][j] == 1) {
						main_grid[i][j + 1] = 1;
						main_grid[i][j] = 0;
					}
				}
			}
		}
	}
}

bool PieceGravityMovement() {
	int i, j;
	bool flag = true;
	for (j = 20; j < 40; j++) {
		for (i = 39; i >= 0; i--) {
			if (main_grid[i][j] == 1) {
				if (main_grid[i + 1][j] == 5 || main_grid[i + 1][j] == 2)
					return true;
			}
		}
	}
	for (j = 20; j < 40; j++) {
		for (i = 39; i >= 0; i--) {
			if (main_grid[i][j] == 1) {
				main_grid[i + 1][j] = 1;
				main_grid[i][j] = 0;
			}
		}
	}
	return false;
}

void PieceFreeze() {
	int k, l;
	for (k = 20; k < 40; k++) {
		for (l = 0; l <= 40; l++) {
			if (main_grid[l][k] == 1)
				main_grid[l][k] = 2;
		}
	}
}

void NextPieceDisp(int piece_choice) {
	int x = 9, y = 25, i, j;
	for (i = y; i <= y + 5; i++) {
		for (j = x - 1; j <= x + 5; j++)
			main_grid[i][j] = 0;
	}
	if (piece_choice == 0)
		main_grid[y][x] = main_grid[y][x + 1] = main_grid[y + 1][x] = main_grid[y + 1][x + 1] = 3;	//sqaure;
	if (piece_choice == 1)
		main_grid[y][x] = main_grid[y + 1][x] = main_grid[y + 2][x] = main_grid[y + 2][x - 1] = 3;	//reverse L;
	if (piece_choice == 2)
		main_grid[y][x] = main_grid[y + 1][x] = main_grid[y + 2][x] = main_grid[y + 2][x + 1] = 3;	//L;
	if (piece_choice == 3)
		main_grid[y][x] = main_grid[y + 1][x] = main_grid[y + 2][x] = main_grid[y + 3][x] = 3;	//straight line;
	if (piece_choice == 4)
		main_grid[y][x] = main_grid[y][x + 1] = main_grid[y + 1][x + 1] = main_grid[y + 1][x + 2] = 3;	//z;
	if (piece_choice == 5)
		main_grid[y][x] = main_grid[y][x + 1] = main_grid[y + 1][x] = main_grid[y + 1][x - 1] = 3;	//reverse z;
	if (piece_choice == 6)
		main_grid[y][x] = main_grid[y + 1][x - 1] = main_grid[y + 1][x] = main_grid[y + 1][x + 1] = 3;	//reverse t;
}

void DrawPieces() {
	int i, j;
	for (i = 0; i <= 50; i++) {
		for (j = 0; j <= 60; j++) {
			if (i >= 10 && j >= 20) {
				if (main_grid[i][j] == 1)
					DrawRectangle(j * 10, i * 10, 10, 10, YELLOW);
				if (main_grid[i][j] == 2)
					DrawRectangle(j * 10, i * 10, 10, 10, RED);
				if (main_grid[i][j] == 1 || main_grid[i][j] == 2) {
					DrawRectangle(j * 10, i * 10, 1, 10, BLACK);
					DrawRectangle(j * 10, (i * 10) + 9, 10, 1, BLACK);
					DrawRectangle(j * 10, i * 10, 1, 10, BLACK);
					DrawRectangle((j * 10) + 9, i * 10, 1, 10, BLACK);
				}
			}
			if (main_grid[i][j] == 3) {
				DrawRectangle(j * 10, i * 10, 10, 10, GREEN);
				DrawRectangle(j * 10, i * 10, 1, 10, BLACK);
				DrawRectangle(j * 10, (i * 10) + 9, 10, 1, BLACK);
				DrawRectangle(j * 10, i * 10, 1, 10, BLACK);
				DrawRectangle((j * 10) + 9, i * 10, 1, 10, BLACK);
			}
		}
	}
}

void ScoringSystem() {
	int complete_rows = 0, i, j, k;
	for (i = 10; i < 40; i++) {
		int row_ctr = 0;
		for (j = 20; j < 40; j++) {
			if (main_grid[i][j] == 2)
				row_ctr++;
		}
		if (row_ctr == 20) {
			complete_rows++;
			score += (20 + (complete_rows * 10));
			for (j = 20; j < 40; j++) {
				main_grid[i][j] = 0;
				for (k = i - 1; k >= 10; k--) {
					if (main_grid[k][j] == 2) {
						main_grid[k + 1][j] = 2;
						main_grid[k][j] = 0;
					}
				}
			}

		}
	}
}

bool CheckGameOver() {
	int j;
	for (j = 20; j < 40; j++) {
		if (main_grid[10][j] == 2)
			return true;
	}
	return false;
}

void RotatePiece() {
	int i, j, min_i=100, max_i=0, min_j=100, max_j=0;
	for (i = 10; i < 40; i++) {
		for (j = 20; j < 40; j++) {
			if (main_grid[i][j] == 1) {
				min_i = min(min_i, i);
				max_i = max(max_i, i);
				min_j = min(min_j, j);
				max_j = max(max_j, j);
			}
		}
	}
	int cur_h = max_i - min_i + 1, cur_w = max_j - min_j + 1;
	if (cur_h > 0 && cur_w > 0) {
		vector<vector<int>> rotated_obj(cur_w, vector<int>(cur_h, 0));
		for (i = min_i; i <= max_i; i++) {
			for (j = min_j; j <= max_j; j++) {
				if (main_grid[i][j] == 1)
					rotated_obj[j - min_j][i - min_i] = main_grid[i][j];
			}
		}
		for (i = 0; i < cur_w; i++) {
			for (j = 0; j < cur_h / 2; j++) {
				int temp = rotated_obj[i][j];
				rotated_obj[i][j] = rotated_obj[i][cur_h - j - 1];
				rotated_obj[i][cur_h - j - 1] = temp;
			}
		}
		bool is_rotation_possible = true;
		for (i = min_i; i <= min_i + cur_w - 1; i++) {
			for (j = min_j; j <= min_j + cur_h - 1; j++) {
				if (main_grid[j][i] != 1 && main_grid[j][i] != 0)
					is_rotation_possible = false;
			}
		}
		if (is_rotation_possible) {
			for (i = min_i; i <= max_i; i++) {
				for (j = min_j; j <= max_j; j++) {
					if (main_grid[i][j] == 1)
						main_grid[i][j] = 0;
				}
			}
			for (i = min_i; i <= min_i + cur_w - 1; i++) {
				for (j = min_j; j <= min_j + cur_h - 1; j++) {
					if (rotated_obj[i - min_i][j - min_j] == 1)
						main_grid[i][j] = rotated_obj[i - min_i][j - min_j];
				}
			}
		}
	}
}

int main() {
	InitWindow(600, 500, "Tetris");
	SetTargetFPS(60);
	srand(time(0));
	PreGameRun();
	clock_t cur, prv;
	prv = clock(); 
	bool PieceNeeded = true, isGameOver = false;
	int piece_choice = rand() % 7;
	while (!IsKeyDown(KEY_E)) {
		BeginDrawing();
		if (isGameOver) {
			DrawRectangle(150, 150, 300, 200, ORANGE);
			DrawText(TextFormat("GAME OVER"), 200, 200, 30, BLACK);
		}
		else {
			DrawMainGUI();
			cur = clock();
			if (PieceNeeded) {
				PieceGen(piece_choice);
				PieceNeeded = false;
				piece_choice = rand() % 7;
				NextPieceDisp(piece_choice);
			}
			if ((double)cur - (double)prv >= 5000 * GetFrameTime()) {
				prv = cur;
				PieceNeeded = PieceGravityMovement();
				if (PieceNeeded) {
					PieceFreeze();
					ScoringSystem();
					isGameOver = CheckGameOver();
				}
				PiecePlayerMovement();
				if (IsKeyDown(KEY_ENTER)) {
					RotatePiece();
				}
			}
			DrawPieces();
		}
		EndDrawing();
	}
	CloseWindow();
}
