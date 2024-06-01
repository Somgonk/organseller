#ifndef ORGAN_H_HEADER_GUARD
#define ORGAN_H_HEADER_GUARD

#include "raylib.h"

class Organ {
  public:
    Organ(Texture2D texure, Vector2 pos, float scale);
    void Drag(Rectangle dropArea);
    void Draw(Rectangle area, float opacity);
    void Scale(float scaleFactor);
    void ActivateIfVisible(Rectangle area);
  private:
    Texture2D texture;
    Rectangle textureRec;
    Vector2 initPos;
    int value;
    bool dragging = false;
    bool show = true;
    bool active = false;
    bool harvested = false;
};

#endif
