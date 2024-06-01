#include "ui.h"

Button::Button(Rectangle buttonRec, Color color) {
  this->rec.x = buttonRec.x;
  this->rec.y = buttonRec.y;
  this->rec.width = buttonRec.width;
  this->rec.height = buttonRec.height;
  this->color = color;
  show = true;
}

Button::Button(string text, int size, Vector2 pos, Color color) {
  this->rec.x = pos.x;
  this->rec.y = pos.y;
  this->rec.width = MeasureText(text.c_str(), size);
  this->rec.height = size;
  this->color = color;
  this->text = text;
  show = true;
}

bool Button::IsPressed() {
  return (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), rec));
}

void Button::Scale(float scaleFactor) {
  rec.x *= scaleFactor;
  rec.y *= scaleFactor;
  rec.width *= scaleFactor;
  rec.height *= scaleFactor;
}

void Button::Draw() {
  Color fillColor = color;
  if (CheckCollisionPointRec(GetMousePosition(), rec)) {
    fillColor = ColorBrightness(color, .5);
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      fillColor = ColorBrightness(color, -.3);
    }
  }
  if (show) {
    DrawRectangleRec(rec, fillColor);
    if (text != "") {
      DrawText(text.c_str(), rec.x, rec.y + 2.5, rec.height - 5, BLACK);
    }
  }
}

void Button::Show() {
  show = true;
}

void Button::Hide() {
  show = false;
}
