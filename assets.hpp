#include "raylib.h"
#include "libs/raymath.h"
#include <list>

namespace sceneryAssets{
    Model Models[2] = {LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 2.0f)), LoadModelFromMesh(GenMeshCube(0.5f, 3.0f, 2.0f))};//Raylib.LoadModel("assets/cube.obj");
    //Texture Textures[] = {};
}

namespace playerAssets{
    Model Models = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 2.0f));//Raylib.LoadModel("assets/cube.obj"); 
    //Texture Textures[] = {};
}

namespace noteAssets{
    Model Models = LoadModelFromMesh(GenMeshCube(1.0f,1.0f,1.0f));
    //Texture Textures[] = {};
}
