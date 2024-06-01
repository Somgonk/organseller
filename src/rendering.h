#ifndef RENDERING_H_HEADER_GUARD
#define RENDERING_H_HEADER_GUARD

#include <raylib.h>

void DrawStaticTextureRec(Texture2D texture, Rectangle textureRec, Rectangle viewRec, float opacity);

void DrawOutline(Rectangle area, float minSize, float maxSize);

#endif
