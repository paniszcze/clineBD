#include "utils.h"

float GetScaleFitted(int src_width,
                     int src_height,
                     int dst_width,
                     int dst_height)
{
    return MIN((float)dst_width / src_width, (float)dst_height / src_height);
}

Rectangle ScaleRec(Rectangle rec, float scale)
{
    return (Rectangle){
        rec.x * scale,
        rec.y * scale,
        rec.width * scale,
        rec.height * scale,
    };
}

Rectangle TranslateRec(Rectangle rec, Vector2 vec)
{
    return (Rectangle){
        rec.x + vec.x,
        rec.y + vec.y,
        rec.width,
        rec.height,
    };
}
