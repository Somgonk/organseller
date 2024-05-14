#include "raylib.h"

#include "rlgl.h"

// Function Declarations
void DrawHarvest();

// Options
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const int TARGET_FPS = 60;

// Game States
enum States { home, tools, harvest, sell };
States GameState = harvest;

// Game Variables
void IncrementMonth();
void IncrementYear();
void MakeDebtPayment(int amount);
unsigned int debt;
unsigned int cash;
double apr = 0.07;
unsigned short int month;
unsigned short int year;

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Organ Seller");
  Camera2D camera = {0};
  camera.zoom = 1.0f;
  GetWorkingDirectory();
  Texture2D texture = LoadTexture("resources/test.png");

  SetTargetFPS(TARGET_FPS);

  while (!WindowShouldClose()) {
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
      // Get the world point that is under the mouse
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

      // Set the offset to where the mouse is
      camera.offset = GetMousePosition();

      // Set the target to match, so that the camera maps the world space point
      // under the cursor to the screen space point under the cursor at any zoom
      camera.target = mouseWorldPos;

      // Zoom increment
      const float zoomIncrement = 0.125f;

      camera.zoom += (wheel * zoomIncrement);
      if (camera.zoom < zoomIncrement)
        camera.zoom = zoomIncrement;
    }
    BeginDrawing();
    BeginMode2D(camera);
    ClearBackground(DARKGRAY);
    if (GameState == harvest) {
      DrawHarvest();
    }
    const int texture_x = SCREEN_WIDTH / 2 - texture.width / 2;
    const int texture_y = SCREEN_HEIGHT / 2 - texture.height / 2;
    DrawTexture(texture, texture_x, texture_y, WHITE);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void DrawHarvest() {

  DrawRectangle(375, 200, 50, 50, WHITE);
  Vector2 mouse = GetMousePosition();
}
