//standard c++ headers
#include <list>
#include <iostream>

//raylib headers
#include "raylib.h"
#include "libs/raymath.h"

//våra egna headers 
#include "player.hpp"
#include "scenery.hpp"
#include "note.hpp"


void drawEverything(Camera3D& cam, Player& plObj, std::list<Scenery>& scObjs)
{
    //setup
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(cam);

    //rita spelaren
    plObj.drawPlayer();

    //rita världen
    DrawPlane((Vector3){0.0f,-0.6f,0.0f}, (Vector2){60.0f, 50.0f}, GREEN);
    DrawPlane((Vector3){0.0f,-0.59f,0.0f}, (Vector2){9.5f, 50.0f}, GRAY);

    //rita dekorationer
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
    //bredden och höjden på skärmen
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    //öppna ett nytt fönster
    InitWindow(screenWidth, screenHeight, "Rythm Rally");
    SetTargetFPS(60);

    //skapa en ny kamera
    Camera3D camera = {0};
    
    camera.position = (Vector3){0.0f, 6.44f, -6.1f};
    camera.target = (Vector3){0.0f, 2.0f, 1.0f};
    camera.up = (Vector3){0.0f, 0.69f, 0.15f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    

    Player playerObject; //skapa spelaren
    std::list<Scenery> sceneryObjects; //lista över alla dekorationsobjekt
    sceneryObjects.push_back(Scenery(0)); //lägg till ett nytt dekorationsobjekt i listan

    //huvudloop
    while (!WindowShouldClose())
    {
        playerObject.playerInput(); //har spelaren tryckt på en knapp?
        std::cout << GetFrameTime() << "\n";

        //flytta varje dekoration och kontrollera om den fortfarande behövs
        for(Scenery& sc : sceneryObjects)
        {
            sc.moveScenery();
            if(sc.outOfBounds == true)
            {
                sc = Scenery(1);
            }
        }
        drawEverything(camera, playerObject, sceneryObjects); //rita världen

    }

    CloseWindow();
    
}

