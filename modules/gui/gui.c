#include "gui.h"

#define RAYGUI_IMPLEMENTATION
#include "../../external/raygui.h"

void DisplayGui(char *img_path, Rectangle *frames, int frames_count)
{
    const int initial_width = 900;
    const int initial_height = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(initial_width, initial_height, "ClineBD");
    SetTargetFPS(24);

    Font pixantiqua = LoadFont("fonts/pixantiqua.png");
    GuiSetFont(pixantiqua);
    Color highlight = Fade(GOLD, 0.32);

    Image current_page = LoadImage(img_path);
    Texture2D page = LoadTextureFromImage(current_page);
    Rectangle scaled_frames[frames_count];

    int curr_frame = -1;
    int mouse_hover_rec = -1;

    while (!WindowShouldClose())
    {
        int screen_width = GetScreenWidth();
        int screen_height = GetScreenHeight();

        float img_scale = GetScaleFitted(page.width, page.height, screen_width / 2, screen_height);
        Vector2 page_position = (Vector2){
            screen_width / 2 - page.width * img_scale / 2,
            screen_height / 2 - page.height * img_scale / 2,
        };

        const float num_font_size = 100.f * img_scale;
        const float spacing = num_font_size * 0.08;

        // Source image will be fitted into the window, so all the frames need to be scaled accordingly
        for (int i = 0; i < frames_count; i++)
        {
            scaled_frames[i] = TranslateRec(ScaleRec(frames[i], img_scale), page_position);
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

            // Draw page image
            DrawTextureEx(page, page_position, 0.f, img_scale, WHITE);

            // Draw frame highlights
            for (int i = 0; i < frames_count; i++)
            {
                Rectangle frame = scaled_frames[i];
                bool is_highlighted = i == curr_frame || i == mouse_hover_rec;

                DrawRectangleRec(frame, is_highlighted ? Fade(highlight, 0.64) : highlight);
                DrawRectangleLinesEx(frame, 3.f, highlight);

                if (is_highlighted)
                {
                    char buffer[32];
                    snprintf(buffer, sizeof(buffer), "%d", i + 1);
                    Vector2 text_size = MeasureTextEx(pixantiqua, buffer, num_font_size, spacing);
                    DrawTextEx(pixantiqua, buffer, (Vector2){frame.x + frame.width / 2 - text_size.x / 2, frame.y + frame.height / 2 - text_size.y / 2}, num_font_size, spacing, WHITE);
                }
            }
        }
        EndDrawing();
    }

    UnloadImage(current_page);
    UnloadTexture(page);
    UnloadFont(pixantiqua);
    CloseWindow();
}