#include <iostream>
#include "raylib.h"

using namespace std;

int main()
{
	InitWindow(800, 600, "Fly Bird");
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircle(400, 300, 200, BLUE);

		EndDrawing();
	}
	return 0;
}
