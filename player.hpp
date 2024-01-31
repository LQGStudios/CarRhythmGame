#include "raylib.h"
#include "libs/raymath.h"
#include <list>

struct Player
{
    private:
        float animationProgress = 0.0f;
        int animationDirection = 1;
        bool animatorActive = false;
        int animationCycles = 0;
        
    public: 
        
        float playerXPosition = 0.0f;

        void drawPlayer(Model& playerModel)
        {   
        
            float angle = 0; //sätt vinkeln till 0

            //animera bara om spelaren precis har flyttats
            if(animatorActive == true)
            {
                animationProgress += 0.15f * animationDirection;

                //ändra riktning om spelaren har roterat till ena änden
                if(animationProgress > 1)
                {
                    animationCycles += 1;
                    animationProgress = 1;
                    animationDirection = -1;
                }
                else if(animationProgress < -1)
                {
                    animationCycles += 1;
                    animationProgress = -1;
                    animationDirection = 1;
                }
                
                //återställ rotationen om animationen är slut
                if(animationCycles == 2)
                {
                    if(animationProgress < 0 && animationDirection == -1)
                    {
                        animationCycles = -1;
                        animatorActive = false;
                    }
                    else if(animationProgress > 0 && animationDirection == 1)
                    {
                        animationCycles = -1;
                        animatorActive = false;
                    }
                }
                
                angle = 180 + (animationProgress * 20);
            }

            playerModel.transform = MatrixRotateXYZ((Vector3){0.0f, DEG2RAD * angle, 0.0f}); //rotera modellen
            DrawModel(playerModel, (Vector3){playerXPosition, 0.0f, -1.0f}, 1.0f, RED);//rita modellen
        }

        bool playerInput(Sound& sfx)
        {
            //om en piltangent är nedtryckt, flytta spelaren och starta animationen
            if((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && playerXPosition > -3.0f)
            {
                PlaySound(sfx);
                animationProgress = 0;
                animationDirection = -1;
                animationCycles = 0;
                animatorActive = true;
                playerXPosition -= 1.5f;
            }
            else if((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && playerXPosition < 3.0f)
            {
                PlaySound(sfx);
                animationProgress = 0;
                animationDirection = 1;
                animationCycles = 0;
                animatorActive = true;
                playerXPosition += 1.5f;
            }

            if(IsKeyPressed(KEY_E) || IsKeyPressed(KEY_Q))
            {
                return true;
            }

            return false;
        }

};
