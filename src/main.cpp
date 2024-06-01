#include "raylib.h"
#include "rlgl.h"

#include <iostream>
#include <vector>

#include "rendering.h"
#include "game.h"
#include "ui.h"
#include "organ.h"
#include "dropzone.h"

using namespace std;

// Options
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;
const float ASPECT_RATIO = 16.0 / 9.0;
const int TARGET_FPS = 60;

int debt = 1000;

void InitOrgans();
float ResizeCallback();
void HarvestScene();

vector<Organ> organs;

int main(void) {

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Organ Seller");
  screenWidth = GetScreenWidth();
  screenHeight = GetScreenHeight();
  ResizeCallback();
  InitOrgans();
  Camera2D camera = {0};
  camera.zoom = 1.0f;

  SetTargetFPS(TARGET_FPS);
  HarvestScene();

  CloseWindow();
  return 0;
}

void InitOrgans() {
  organs.push_back((Organ){LoadTexture("resources/kidney.png"), (Vector2){45 * vw, 35 * vh}, vw / (16 * 5)});
  organs.push_back((Organ){LoadTexture("resources/kidney.png"), (Vector2){49 * vw, 35 * vh}, vw / (16 * 5)});

}

float ResizeCallback() {
  float scale = GetScreenWidth() / (float)screenWidth;
  screenWidth = GetScreenWidth();
  screenHeight = GetScreenHeight();

  if (screenWidth > screenHeight) {
    SetWindowSize(screenWidth, screenWidth / ASPECT_RATIO);
  } else {
    SetWindowSize(screenHeight * ASPECT_RATIO, screenHeight);
  }
  vw = GetScreenWidth() / 100.0f;
  vh = GetScreenHeight() / 100.0f;

  // Scale selection area
  area.x *= scale;
  area.width *= scale;
  area.y *= scale;
  area.height *= scale;
  minAreaSize = vw * 2;
  maxAreaSize = vw * 4;
  return scale;
}

void HarvestScene() {
  Texture2D outsideTexture = LoadTexture("resources/outer.png");
  Texture2D insideTexture = LoadTexture("resources/inner.png");
  Texture2D kidneyTexture = LoadTexture("resources/kidney.png");
  Texture2D openBoxTexture = LoadTexture("resources/open_box.png");
  Texture2D closedBoxTexture = LoadTexture("resources/closed_box.png");

  float opacity = 0;

  Button approveSelectionButton {"select", 30, (Vector2){50,50}, GREEN};
  bool selectionApproved = false;

  DropZone organBox {openBoxTexture, closedBoxTexture, (Vector2){30, (52 * vh)}, 0.25f};

  while (!WindowShouldClose()) {
    // resize handling
    if (IsWindowResized()) {
      frameScale = ResizeCallback();

      approveSelectionButton.Scale(frameScale);
      organBox.Scale(frameScale);
      for (int i = 0; i < organs.size(); i++) {
        organs.at(i).Scale(frameScale);
      }
    } else {
      frameScale = 1;
    }

    if (approveSelectionButton.IsPressed() && selectionValid(area, minAreaSize, maxAreaSize)) {
      opacity = 1;
      selectionApproved = true;
      for (int i = 0; i < organs.size(); i++) {
        organs.at(i).ActivateIfVisible(area);
      }

    } 

    if (!selectionApproved) {
      // Starts the selection
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !selectionApproved) {
        mouseStartPos = GetMousePosition();
        area.x = mouseStartPos.x;
        area.y = mouseStartPos.y;
        opacity = 0;
      }
      // Selection sizing 
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !selectionApproved) {
        if (mouseStartPos.x > GetMouseX()) {
          area.x = GetMouseX();
          area.width = mouseStartPos.x - GetMouseX();
        } else {
          area.x = mouseStartPos.x;
          area.width = GetMouseX() - mouseStartPos.x;
        }
        if (mouseStartPos.y > GetMouseY()) {
          area.y = GetMouseY();
          area.height = mouseStartPos.y - GetMouseY();
        } else {
          area.y = mouseStartPos.y;
          area.height = GetMouseY() - mouseStartPos.y;
        }
      } else {
        if (!selectionValid(area, minAreaSize, maxAreaSize)) {
          area = {0,0,0,0};
        } 
      }
    } else {
      // Selection has been made
      for (int i = 0; i < organs.size(); i++) {
        organs.at(i).Drag(organBox.GetRec());
      }

    }

    Rectangle bodyTextureRec = {0, 0, (float)outsideTexture.width, (float)outsideTexture.height};
    Rectangle bodyTextureView = {0, 0, GetScreenHeight() * ((float)outsideTexture.width / outsideTexture.height) * 0.95f, (float)GetScreenHeight() * 0.95f};
    bodyTextureView.x = GetScreenWidth() / 2.0f - bodyTextureView.width / 2.0f;   // Centers x
    bodyTextureView.y = GetScreenHeight() / 2.0f - bodyTextureView.height / 2.0f; // Centers y

    
    BeginDrawing();
      ClearBackground(DARKGRAY);
       
      organBox.Draw();

      DrawTexturePro(outsideTexture, bodyTextureRec, bodyTextureView,(Vector2){0,0},0,WHITE);
      DrawStaticTextureRec(insideTexture, bodyTextureView, area, opacity);

      DrawOutline(area, minAreaSize, maxAreaSize);

      for (int i = 0; i < organs.size(); i++) {
        organs.at(i).Draw(area, opacity);
      }

      approveSelectionButton.Draw();

    EndDrawing();
  }
}
