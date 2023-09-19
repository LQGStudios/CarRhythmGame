#include "raylib.h"
#include "libs/raymath.h"
#include <list>
#include "player.hpp"
#include "scenery.hpp"


void drawEverything(Camera3D& cam, Player& plObj, std::list<Scenery>& scObjs)
{
    
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(cam);
    plObj.drawPlayer();

    DrawPlane((Vector3){0.0f,-0.6f,0.0f}, (Vector2){60.0f, 50.0f}, GREEN);
    DrawPlane((Vector3){0.0f,-0.59f,0.0f}, (Vector2){9.5f, 50.0f}, GRAY);

    for(Scenery& sc : scObjs)
    {
        sc.drawSceneryModel();
    }

    //Rita FPS och avsluta ritande
    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
}


int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    

    InitWindow(screenWidth, screenHeight, "Rythm Rally");
    SetTargetFPS(60);

    Camera3D camera = {0};
    
    camera.position = (Vector3){0.0f, 6.44f, -6.1f};
    camera.target = (Vector3){0.0f, 2.0f, 1.0f};
    camera.up = (Vector3){0.0f, 0.69f, 0.15f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    

    Player playerObject;
    std::list<Scenery> sceneryObjects;
    sceneryObjects.push_back(Scenery(1));

    while (!WindowShouldClose())
    {
        playerObject.playerInput();
        for(Scenery& sc : sceneryObjects)
        {
            sc.moveScenery();
        }
        drawEverything(camera, playerObject, sceneryObjects);

    }

    CloseWindow();
    
}

