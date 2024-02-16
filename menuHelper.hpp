#include "raylib.h"
#include <iostream>

struct menuHelper
{
    int bgFadeTo = 1;
    int bgFadeFrom = 0;
    int fadeProgress = 0;

    void drawFadeBg(Texture2D (&textures)[3])
    {
        float fadeAmount = fadeProgress/180.0f;
        
        if(fadeAmount >= 2.0f)
        {
            fadeProgress = 0;
            fadeAmount = 0;
            bgFadeFrom += 1;
            if(bgFadeFrom > 2)
            {
                bgFadeFrom = 0;
            }
            
            bgFadeTo += 1;
            if(bgFadeTo > 2)
            {
                bgFadeTo = 0;
            }
        }

        if(fadeAmount > 1.0f)
        {
            fadeAmount = 1.0f;
        }

        int t1Fade = (int)255 - 255 * fadeAmount;
        DrawTexturePro(textures[bgFadeFrom], {0,0,1920,1080}, {0,0,1280,720}, {0,0}, 0.0f, Color{255,255,255, (unsigned char)t1Fade});
        DrawTexturePro(textures[bgFadeTo], {0,0,1920,1080}, {0,0,1280,720}, {0,0}, 0.0f, Color{255,255,255, (unsigned char)(255 * fadeAmount)});
        fadeProgress += 1;
    }

    void drawRoundedSquare(int x, int y, int w, int h, Color c)
    {
        float circleRadius = floor((w * 0.125f + h * 0.25f)/2.0f);

        DrawCircleSector({x + circleRadius, y + circleRadius}, circleRadius, 180, 270, 180, c);
        DrawCircleSector({x + (w - circleRadius), y + circleRadius}, circleRadius, 90, 180, 180, c);

        DrawRectangle(x + circleRadius, y, w - circleRadius * 2, circleRadius, c);

        DrawRectangle(x, y + circleRadius, w, h - circleRadius * 2, c);

        DrawRectangle(x + circleRadius, y + (h - circleRadius), w - circleRadius * 2, circleRadius, c);
        
        DrawCircleSector({x + circleRadius, y + (h - circleRadius)}, circleRadius, 270, 360, 180, c);
        DrawCircleSector({x + (w - circleRadius), y + (h - circleRadius)}, circleRadius, 0, 90, 180, c);
    }
};

