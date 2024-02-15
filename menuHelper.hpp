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
        std::cout << fadeAmount << "\n";
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
};
