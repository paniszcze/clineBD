#include <stdio.h>
#include "raylib.h"

#include "modules/gui/gui.h"

#define SIZEOF(a) (sizeof(a) / sizeof(a[0]))

int main(void)
{
    char *image_path = "samples/robin-des-bois_04_05.jpg";

    // Data will be provided by the processing unit; for now,
    // it has been entered manually to get raylib up and running
    Rectangle frames[] = {
        (Rectangle){17, 23, 295, 421},
        (Rectangle){323, 25, 299, 421},
        (Rectangle){633, 27, 295, 420},
        (Rectangle){18, 457, 295, 414},
        (Rectangle){323, 459, 302, 414},
        (Rectangle){634, 459, 295, 414},
        (Rectangle){19, 882, 458, 426},
        (Rectangle){486, 886, 445, 426},
    };
    const int frames_count = SIZEOF(frames);

    DisplayGui(image_path, frames, frames_count);

    return 0;
}