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
        Model playerModel = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 2.0f));//Raylib.LoadModel("assets/cube.obj");
        
    public: 
        float playerXPosition = 0.0f;

        void drawPlayer()
        {   
        
            float angle = 0;
            if(animatorActive == true)
            {
                animationProgress += 0.1f * animationDirection;
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
                
                if(animationProgress < 0 && animationCycles == 2)
                {
                    animationCycles = -1;
                    animatorActive = false;
                }
                
                angle = 180 + (animationProgress * 20);
            }

            playerModel.transform = MatrixRotateXYZ((Vector3){0.0f, DEG2RAD * angle, 0.0f}); 
            DrawModel(playerModel, (Vector3){playerXPosition, 0.0f, -1.0f}, 1.0f, RED);
            DrawCubeWires((Vector3){playerXPosition, 0.0f, -1.0f}, 1.0f, 1.0f, 2.0f, BLACK);
        }

        void playerInput()
        {
            if(IsKeyPressed(KEY_RIGHT) && playerXPosition > -3.0f)
            {
                animationProgress = 0;
                animationDirection = -1;
                animationCycles = 0;
                animatorActive = true;
                playerXPosition -= 1.5f;
            }
            else if(IsKeyPressed(KEY_LEFT) && playerXPosition < 3.0f)
            {
                animationProgress = 0;
                animationDirection = -1;
                animationCycles = 0;
                animatorActive = true;
                playerXPosition += 1.5f;
            }
        }

};
