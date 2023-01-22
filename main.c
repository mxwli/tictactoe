#include"raylib.h"
#include"stdlib.h"
#define gridSize 200
#define sW (3*gridSize)
#define sH (3*gridSize+50)
#define lThckness 10
int grid[3][3];
int toplay = 1;
/* 	-2: O wins
	-1: O to play
	 0: Draw
	 1: X to play
	 2: X wins
*/
int main() {
	InitWindow(sW, sH, "Tic Tac Toe");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		
		//DISPLAY GAME STATUS
		if(toplay == -1) DrawText("O to play!", 10, 3*gridSize+10, 30, BLACK);
		if(toplay == 0) DrawText("Draw!", 10, 3*gridSize+10, 30, BLACK);
		if(toplay == 1) DrawText("X to play!", 10, 3*gridSize+10, 30, BLACK);
		if(toplay == -2) DrawText("O wins! SPACE to reset", 10, 3*gridSize+10, 30, BLACK);
		if(toplay == 2) DrawText("X wins! SPACE to reset", 10, 3*gridSize+10, 30, BLACK);

		//GET USER INPUT
		if(IsMouseButtonPressed(0) && (toplay == -1 || toplay == 1)) {
			int x = GetMouseX()/gridSize, y = GetMouseY()/gridSize;
			if(x >= 0 && x < 3 && y >= 0 && y < 3 && !grid[x][y]) {
				grid[x][y] = toplay;
				toplay *= -1;
			}
		}
		//RESET THE GAME
		if(IsKeyPressed(KEY_SPACE)) {
			for(int i = 0; i < 3; i++) for(int i2 = 0; i2 < 3; i2++) grid[i][i2] = 0;
			toplay = 1;
		}

		//DRAW BOARD LINES
		//DRAW CURRENT GAME
		DrawRectangleLines(gridSize, 0, gridSize, 3*gridSize, GRAY);
		DrawRectangleLines(0, gridSize, 3*gridSize, gridSize, GRAY);
		DrawRectangleLines(0, 0, 3*gridSize, 3*gridSize, GRAY);
		for(int i = 0; i < 3; i++) {
			for(int i2 = 0; i2 < 3; i2++) {
				if(grid[i][i2] == 1) {
					Vector2 a, b;
					a.x = i*gridSize+10, a.y = i2*gridSize+10; b.x = (i+1)*gridSize-10, b.y=(i2+1)*gridSize-10;
					DrawLineEx(a, b, lThckness, RED);
					float tmp = a.x; a.x = b.x; b.x = tmp;
					DrawLineEx(a, b, lThckness, RED);
				}
				else if (grid[i][i2] == -1) {
					Vector2 a, b;
					a.x = i*gridSize+gridSize/2, a.y = i2*gridSize+gridSize/2;
					DrawCircleV(a, gridSize/2-10, BLUE);
					DrawCircleV(a, gridSize/2-10-lThckness, WHITE);
				}
			}
		}

		//UPDATE GAME STATUS
		for(int i = 0; i < 3; i++) {
			bool eqA = grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0];
			bool eqB = grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i];
			if(eqA) {
				toplay = 2*grid[i][0];
				DrawRectangle(i*gridSize+gridSize/2-lThckness, 0, 2*lThckness, 3*gridSize, GREEN);
				break;
			}
			if(eqB) {
				toplay = 2*grid[0][i];
				DrawRectangle(0,i*gridSize+gridSize/2-lThckness, 3*gridSize, 2*lThckness, GREEN);
				break;
			}
		}
		bool diagA = grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0];
		bool diagB = grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2] && grid[2][0];
		if(diagA) {
			toplay = 2*grid[0][0];
			Vector2 a, b; a.x = 0; a.y = 0; b.x = 3*gridSize; b.y = 3*gridSize;
			DrawLineEx(a, b, 2*lThckness, GREEN);
		}
		if(diagB) {
			toplay = 2*grid[2][0];
			Vector2 a, b; a.x = 0; a.y = 3*gridSize; b.x = 3*gridSize; b.y = 0;
			DrawLineEx(a, b, 2*lThckness, GREEN);
		}
		if(toplay == 1 || toplay == -1) {
			int cnt = 0;
			for(int i = 0; i < 3; i++) for(int i2 = 0; i2 < 3; i2++) cnt += grid[i][i2] != 0;
			if(cnt == 9) toplay = 0;
		}

		EndDrawing();
	}
	CloseWindow();
	return 0;
}
