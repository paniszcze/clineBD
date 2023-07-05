#include <stdio.h>
#include "raylib.h"

#define MIN(a, b) (a) < (b) ? (a) : (b)
#define SIZE(a) sizeof(a) / sizeof((a)[0])

Rectangle ScaleRectangle(Rectangle rec, float scalar);
Rectangle TranslateRectangle(Rectangle rec, Vector2 vec);

int main(void)
{
    const int window_width = 900;
    const int window_height = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(window_width, window_height, "ClineBD");

    Image current_page = LoadImage("samples/robin-des-bois_04_05.jpg");
    Texture2D preview = LoadTextureFromImage(current_page);

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

    const int frames_count = SIZE(frames);
    Rectangle scaled_frames[frames_count] = {0};

    int curr_frame = -1;
    int mouse_hover_rec = -1;

    Font pixantiqua = LoadFont("fonts/pixantiqua.png");
    Color highlight = Fade(GOLD, 0.32);

    while (!WindowShouldClose())
    {
        int screen_width = GetScreenWidth();
        int screen_height = GetScreenHeight();

        float image_scale = MIN((float)screen_height / preview.height, (float)screen_width / preview.width);
        Vector2 preview_position = (Vector2){
            screen_width / 2 - preview.width * image_scale / 2,
            screen_height / 2 - preview.height * image_scale / 2,
        };

        // String buffer and font format for frame numbering
        char buffer[32];
        const float font_size = 100.f * image_scale;
        const float spacing = font_size * 0.08;

        // Source image will be fitted into the window, so all the frames need to be scaled accordingly
        for (int i = 0; i < frames_count; i++)
        {
            scaled_frames[i] = TranslateRectangle(ScaleRectangle(frames[i], image_scale), preview_position);
        }

        // Checking for mouse events
        for (int i = 0; i < frames_count; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), scaled_frames[i]))
            {
                mouse_hover_rec = i;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    curr_frame = i;
                break;
            }
            else
                mouse_hover_rec = -1;

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                curr_frame = -1;
        }

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            DrawTextureEx(preview, preview_position, 0.f, image_scale, WHITE);

            for (int i = 0; i < frames_count; i++)
            {
                bool is_highlighted = i == curr_frame || i == mouse_hover_rec;
                Rectangle frame = scaled_frames[i];
                DrawRectangleRec(frame, is_highlighted ? Fade(highlight, 0.64) : highlight);
                DrawRectangleLinesEx(frame, 3.f, highlight);

                if (is_highlighted)
                {
                    snprintf(buffer, sizeof(buffer), "%d", i + 1);
                    Vector2 text_size = MeasureTextEx(pixantiqua, buffer, font_size, spacing);
                    DrawTextEx(pixantiqua, buffer, (Vector2){frame.x + frame.width / 2 - text_size.x / 2, frame.y + frame.height / 2 - text_size.y / 2}, font_size, spacing, WHITE);
                }
            }
        }
        EndDrawing();
    }

    UnloadImage(current_page);
    UnloadTexture(preview);
    UnloadFont(pixantiqua);
    CloseWindow();

    return 0;
}

Rectangle ScaleRectangle(Rectangle rec, float scalar)
{
    return (Rectangle){
        rec.x * scalar,
        rec.y * scalar,
        rec.width * scalar,
        rec.height * scalar,
    };
}

Rectangle TranslateRectangle(Rectangle rec, Vector2 vec)
{
    return (Rectangle){
        rec.x + vec.x,
        rec.y + vec.y,
        rec.width,
        rec.height,
    };
}