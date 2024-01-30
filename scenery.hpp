#include "raylib.h"
#include "libs/raymath.h"
#include <list>

struct Scenery
{
    public: 
        int selectedModel;
        Vector2 sceneryPosition =  (Vector2){5.0f, 27.0f};
        bool outOfBounds = false;

        void moveScenery()
        {
            //Z positionen
            sceneryPosition.y -= 0.2f;
            //kamerans z-position är ungefär -7, och om objektet är bakom kameran behövs det inte längre
            if(sceneryPosition.y < -7)
            {
                outOfBounds = true;
            }
        }

        
        Scenery(int modelIndex) //ny dekoration
        {
            selectedModel = modelIndex;
        }

};
