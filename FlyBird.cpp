#include "raylib.h"

#include <cmath>
#include <iostream>
#include <vector>

#define WNDW_W 800
#define WNDW_H 600

#define SEP 200
#define AMP 50
#define FORATDIV2 50
#define VEL 3

#define MIDAOCELL 50

using namespace std;

struct Obstacle {
    int posicio;
    int alcada;
};

int main() {
    int posicio = WNDW_W;
    bool stop = false;
    int ocell_vel = 3;

    Vector2 posicioOcell = {75, 0};

    InitWindow(WNDW_W, WNDW_H, "Fly Bird");
    SetTargetFPS(60);

    Texture2D tex = LoadTexture("./assets/Nau.png");

    std::vector<Obstacle> obstacles;
    std::vector<Vector2> bales;

    for (int i = 0; i < 20; i++) {
        Obstacle b;
        b.posicio = i * SEP;
        b.alcada = (50.0 * sin((i / (PI * 2.0)) * 25.0)) + WNDW_H / 2.0;

        obstacles.push_back(b);
    }

    while (!WindowShouldClose() and stop != true) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            ocell_vel = -3;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            bales.push_back(posicioOcell);
        }

        posicioOcell.y += ocell_vel;

        Rectangle ocellRect = {posicioOcell.x, posicioOcell.y, MIDAOCELL,
                               MIDAOCELL / 2.0};

        DrawTextureV(tex, posicioOcell, WHITE);

        for (int i = 0; i < obstacles.size(); i++) {
            Rectangle obstRect;
            obstRect.x = obstacles[i].posicio + posicio;
            obstRect.y = WNDW_H - obstacles[i].alcada + FORATDIV2;
            obstRect.width = AMP;
            obstRect.height = obstacles[i].alcada;

            DrawRectangleRec(obstRect, BLUE);

            if (CheckCollisionRecs(ocellRect, obstRect)) {
                stop = true;
            }

            obstRect.y = 0;
            obstRect.height = WNDW_H - obstacles[i].alcada - FORATDIV2;

            DrawRectangleRec(obstRect, BLUE);
            if (CheckCollisionRecs(ocellRect, obstRect)) {
                stop = true;
            }
        }

        for (int i = 0; i < bales.size(); i++) {
            Vector2 &bala = bales[i];
            DrawRectangleV(bala, {5, 2}, RED);
            bala.x += VEL * 2;
            if (bala.x > WNDW_W) {
                bales[i] = bales[bales.size() - 1];
                bales.pop_back();
            }
        }

        posicio -= VEL;

        if (ocell_vel < 3) {
            ocell_vel += 1;
        }

        EndDrawing();
    }
    return 0;
}
