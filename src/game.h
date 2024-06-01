#ifndef GAME_H_HEADER_GUARD
#define GAME_H_HEADER_GUARD

#include "raylib.h"

#include <iostream>
using namespace std;

// Scaling
static int screenWidth = GetScreenWidth();
static int screenHeight = GetScreenHeight();
static float frameScale = 1;


static float vw;
static float vh;

// Game State
enum State {HOME, BUY, HARVEST, SELL};
static State GameState = HARVEST;

// Area Drag Selection
static Vector2 mouseStartPos;
static Rectangle area = {0,0,0,0};
static float minAreaSize;
static float maxAreaSize;

static bool selectionValid(Rectangle area, float minSize, float maxSize) {
  return (area.width <= maxSize && area.height <= maxSize) && (area.width >= minSize && area.height >= minSize);
}

// Organ Dragging
static bool draggingSomething = false;

#endif
