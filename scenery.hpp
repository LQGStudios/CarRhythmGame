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
        void drawSceneryModel()
        {   
            DrawModel(selectedModel, (Vector3){sceneryPosition.x, 0.0f, sceneryPosition.y}, 1.0f, BLUE);
        }
        void moveScenery()
        {
            //Z positionen
            sceneryPosition.y -= 0.2f;
        }
        
        Scenery(int modelIndex)
        {
            selectedModel = sceneryModels[modelIndex];
        }

        
};
