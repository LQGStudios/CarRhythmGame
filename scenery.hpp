#include "raylib.h"
#include "libs/raymath.h"
#include "assets.hpp"
#include <list>

struct Scenery
{
    private:
        Model selectedModel;
        Vector2 sceneryPosition =  (Vector2){5.0f, 27.0f};
    
    public: 
        bool outOfBounds = false;

        void drawSceneryModel()
        {   
            DrawModel(selectedModel, (Vector3){sceneryPosition.x, 0.0f, sceneryPosition.y}, 1.0f, BLUE);//rita modellen
        }

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
            selectedModel = sceneryAssets::Models[modelIndex];
        }

};
