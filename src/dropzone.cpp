#include "dropzone.h"

DropZone::DropZone(Texture2D openTexture, Texture2D closedTexture, Vector2 pos, float scale) {
  this->openTexture = openTexture;
  this->closedTexture = closedTexture;
  this->pos = pos;
  this->scale = scale;
  this->open = true;
}

void DropZone::Draw() {
  Rectangle textureRec = {0, 0, (float)openTexture.width, (float)openTexture.height};
  Rectangle destRec = {pos.x, pos.y, (float)openTexture.width * scale, (float)openTexture.height * scale};
  DrawTexturePro((open? openTexture: closedTexture), textureRec, destRec, (Vector2){0,0}, 0, WHITE);
}

Rectangle DropZone::GetRec() {
  return (Rectangle){pos.x, pos.y, (float)openTexture.width * scale, (float)openTexture.height * scale};
}

void DropZone::Scale(float scaleFactor) {
  this->pos.x *= scaleFactor;
  this->pos.y *= scaleFactor;
  this->scale *= scaleFactor;
} 

void DropZone::CloseZone() {
  open = false;
}
bool DropZone::IsOpen() {
  return open;
}
