#include "raylib.h"
#include "libs/raymath.h"
#include <list>

struct Scenery
{
    private:
        Model selectedModel;
        Model sceneryModels[2] = {LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 2.0f)), LoadModelFromMesh(GenMeshCube(0.5f, 3.0f, 2.0f))};//Raylib.LoadModel("assets/cube.obj");
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

        void deleteScenery()
        {
            UnloadModel(selectedModel);
            for (int i = 0; i < 2; i++)
            {
                UnloadModel(sceneryModels[i]);
            }
            
        }
        
        Scenery(int modelIndex) //ny dekoration
        {
            selectedModel = sceneryModels[modelIndex];
        }

};
