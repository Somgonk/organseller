#ifndef UI_H_HEADER_GUARD
#define UI_H_HEADER_GUARD

#include "raylib.h"
#include <string>

using namespace std;

class Button {
  public:
    Button(Rectangle buttonRec, Color color);
    Button(string text, int size, Vector2 pos, Color color);
    bool IsPressed();
    void Scale(float scaleFactor);
    void Draw();
    void Show();
    void Hide();
  private:
    Rectangle rec;
    bool show;
    Color color;
    string text;
};

#endif
