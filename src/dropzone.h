#ifndef DROPZONE_H_HEADER_GUARD
#define DROPZONE_H_HEADER_GUARD

#include "raylib.h"


class DropZone {
  public:
    DropZone(Texture2D openTexture, Texture2D closedTexture, Vector2 pos, float scale);
    void Draw();
    void Scale(float scaleFactor);
    Rectangle GetRec();
    void CloseZone();
    bool IsOpen();
  private:
    Texture2D openTexture;
    Texture2D closedTexture;
    Vector2 pos;
    float scale;
    bool open;
};

#endif
