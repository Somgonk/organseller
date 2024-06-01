#include "organ.h"
#include "rendering.h"
#include "game.h"

#include <stdlib.h>

Organ::Organ(Texture2D texture, Vector2 pos, float scale) {
  this->texture = texture;
  this->textureRec.x = pos.x;
  this->textureRec.y = pos.y;
  this->textureRec.width = texture.width * scale;
  this->textureRec.height = texture.height * scale;
  this->initPos = pos;
}

void Organ::Drag(Rectangle dropArea) {
  if (!active) return;
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), textureRec) && !draggingSomething && show) {
    dragging = true;
    draggingSomething = true;
  }
  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && dragging) {
    dragging = false;
    draggingSomething = false;
    if (CheckCollisionRecs(textureRec, dropArea)) {
      textureRec.x = dropArea.width / 2.0f - (textureRec.width / 2.0f); 
      textureRec.y = dropArea.height / 2.0f - (textureRec.height / 2.0f);
      show = false;
      active = false;
      harvested = true;
    }
  }
  if (dragging) {
    Vector2 change = GetMouseDelta();
    textureRec.x += change.x;
    textureRec.y += change.y;
  }
}

void Organ::Scale(float scaleFactor) {
  textureRec.x *= scaleFactor;
  textureRec.y *= scaleFactor;
  textureRec.width *= scaleFactor;
  textureRec.height *= scaleFactor;
  initPos.x *= scaleFactor;
  initPos.y *= scaleFactor;
}

void Organ::Draw(Rectangle area, float opacity) {
  if (abs((float)textureRec.x - initPos.x) >= 1 || abs((float)textureRec.y - initPos.y) >= 1) {
    area = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};
  } 
  if (show) {
    DrawStaticTextureRec(texture, textureRec, area, opacity);
  }
}

void Organ::ActivateIfVisible(Rectangle area) {
  if (CheckCollisionRecs(textureRec, area)) {
    active = true;
  }
}
