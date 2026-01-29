#include "raylib.h"

#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>

#define WNDW_W 800
#define WNDW_H 600

#define SEP 200
#define AMP 50
#define FORATDIV2 64
#define VEL 3

#define MIDAOCELL 64

using namespace std;

struct Obstacle {
    int posicio;
    int alcada;
};

int main() {
    int posicio = WNDW_W;
    bool stop = false;
    int ocell_vel = 3;
    unsigned int frame = 0;
    unsigned int record = 0;

    Vector2 posicioOcell = {75, 0};

    InitWindow(WNDW_W, WNDW_H, "Fly Bird");
    SetTargetFPS(60);

    Texture2D tex = LoadTexture("./assets/Nau.png");
    Texture2D flamaTex = LoadTexture("./assets/Flama.png");

    if (FileExists("./saves/last-record.txt")) {
        int size;
        record =
            *((unsigned int *)LoadFileData("./saves/last-record.txt", &size));
    }

    std::vector<Obstacle> obstacles;

    for (int i = 0; i < 20; i++) {
        Obstacle b;
        b.posicio = i * SEP;
        b.alcada = (50.0 * sin((i / (PI * 2.0)) * 25.0)) + WNDW_H / 2.0;

        obstacles.push_back(b);
    }

    while (!WindowShouldClose() and stop != true) {

        std::string text =
            "Time: " + to_string(frame) + " / " + to_string(record);

        DrawText(text.c_str(), 5, 5, 24, WHITE);

        frame++;

        BeginDrawing();
        ClearBackground(BLACK);

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsKeyDown(KEY_SPACE)) {
            ocell_vel = -3;
        }

        posicioOcell.y += ocell_vel;

        Rectangle ocellRect = {posicioOcell.x, posicioOcell.y, MIDAOCELL,
                               MIDAOCELL};

        DrawTextureEx(tex, posicioOcell, 0, 2, WHITE);

        Vector2 posicioFlama = posicioOcell;
        posicioFlama.x -= MIDAOCELL;

        Rectangle flamaRec{(float)(frame % 4) * 32, 0, 32, 32};

        DrawTexturePro(flamaTex, flamaRec,
                       {posicioFlama.x, posicioFlama.y, 64, 64}, {0, 0}, 0,
                       WHITE);

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

        posicio -= VEL;

        if (ocell_vel < 3) {
            ocell_vel += 1;
        }

        EndDrawing();
    }

    if (frame > record) {
        SaveFileData("./saves/last-record.txt", &frame, sizeof(unsigned int));
    }

    return 0;
}
