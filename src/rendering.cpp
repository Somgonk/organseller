#include "rendering.h"

#include <iostream>
#include "game.h"

// texture is the texture to be drawn
// textureRec scales and positions the texture
// viewRec is the "window" to the texture in reference to screen space
void DrawStaticTextureRec(Texture2D texture, Rectangle textureRec, Rectangle viewRec, float opacity) {
  // Makes the coords make sense (idk why theyre swapped)
  textureRec.x *= -1;
  textureRec.y *= -1;
  
  // Texture Scaling
  textureRec.width = texture.width / (textureRec.width / viewRec.width);
  textureRec.height = texture.height / (textureRec.height / viewRec.height);

  // View Window
  textureRec.x = (viewRec.x + textureRec.x) * (1 / (viewRec.width / textureRec.width));
  textureRec.y = (viewRec.y + textureRec.y) * (1 /  (viewRec.height / textureRec.height));

  DrawTexturePro(texture, textureRec, viewRec, (Vector2){0, 0}, 0, ColorAlpha(WHITE, opacity));
}

void DrawOutline(Rectangle area, float minSize, float maxSize) {
  Color lineColor = GREEN;
  if (!selectionValid(area, minSize, maxSize)) {
    lineColor = RED;
      }

  DrawRectangleLinesEx(area, 2, lineColor);
}
