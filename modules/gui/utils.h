#ifndef CLINE_UTILS_H
#define CLINE_UTILS_H

#include "raylib.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

float GetScaleFitted(int src_width, int src_height, int dst_width, int dst_height);
Rectangle ScaleRec(Rectangle rec, float scale);
Rectangle TranslateRec(Rectangle rec, Vector2 vec);

#endif // CLINE_UTILS_H