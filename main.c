#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define FPS 60

#define BAR_HEIGHT 50

#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)

int main() {

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Pong");

    Camera2D camera = {(Vector2){WINDOW_WIDTH/2, WINDOW_HEIGHT/2}, (Vector2){0, 0}, 0, 20};
    Image testImage = LoadImage("test.png");
    Texture2D testTexture = LoadTexture("test.png");
    RenderTexture2D textureWindow = LoadRenderTexture(WINDOW_WIDTH, WINDOW_HEIGHT - BAR_HEIGHT);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();

        Vector2 mouseTexturePosition = GetScreenToWorld2D((Vector2){GetMouseX(), GetMouseY()}, camera);
        mouseTexturePosition = Vector2Add(mouseTexturePosition, (Vector2){testTexture.width /  2, testTexture.height / 2});

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            ImageDrawPixel(&testImage, floor(mouseTexturePosition.x), floor(mouseTexturePosition.y), WHITE);
            testTexture = LoadTextureFromImage(testImage);
        }

        BeginDrawing();

            ClearBackground(BLACK);

            DrawRectangleRec((Rectangle){0, 0, WINDOW_WIDTH, BAR_HEIGHT}, WHITE);

            BeginTextureMode(textureWindow);

                BeginMode2D(camera);
                
                ClearBackground(BLACK);
                //DrawTexture(testTexture, -testTexture.width /  2, -testTexture.height / 2, WHITE);
                DrawTextureRec(testTexture, (Rectangle){0, 0, testTexture.width, -testTexture.height}, (Vector2){-testTexture.width / 2, -testTexture.height / 2}, WHITE);
                DrawCircle(0, 0, 1, RED);

                EndMode2D();

            EndTextureMode();

            DrawTexture(textureWindow.texture, 0, BAR_HEIGHT, WHITE);

            char buffer[6] = "";
            gcvt(mouseTexturePosition.x, 6, buffer); //CHANGE AS OBSOLETE
            DrawText(buffer, 0, BAR_HEIGHT, 20, RED);
            gcvt(mouseTexturePosition.y, 6, buffer); //CHANGE AS OBSOLETE
            DrawText(buffer, 0, BAR_HEIGHT+20, 20, RED);

            DrawFPS(0, 0);

        EndDrawing();

    }

    return 0;
}