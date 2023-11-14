//standard c++ headers
#include <list>
#include <iostream>

//raylib headers
#include "raylib.h"
#include "libs/raymath.h"
#include "libs/raygui.h"

//våra egna headers 
#include "player.hpp"
#include "scenery.hpp"
#include "note.hpp"


unsigned int cycles = 0;
bool transition = false;
int activeScene = 0;


void drawWorld(Camera3D& cam, Player& plObj, std::list<Scenery>& scObjs, std::list<Note>& ntObjs)
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
    
    for(Note& nt : ntObjs)
    {
        nt.drawNoteModel((0.25f * sin(cycles * 10 * PI/180) + 0.25f));
    }
    

    //Rita FPS och avsluta ritande
    EndMode3D();

    DrawFPS(10, 10);

    EndDrawing();
}

void drawMenu()
{
    //setup
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("RYTHM\nRALLY", 500, 50 + 10 * sin(cycles * PI/180), 80, DARKGRAY);
    DrawText("1: Song 1\n2: Song 2\n3: Song 3\n4: Song 4\n5: Song 5\n", 10, 400, 40, DARKGRAY);

    

    if(transition == true)
    {
        DrawCircle(640, 360, cycles * 15, BLACK);
        if(15 * cycles >= 800)
        {
            activeScene = 1;
            transition = false;
        }
    }

    //Rita FPS och avsluta ritande

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
    std::list<Scenery> sceneryObjects;
    std::list<Note> noteObjects; //lista över alla dekorationsobjekt
    sceneryObjects.push_back(Scenery(0)); //lägg till ett nytt dekorationsobjekt i listan
    noteObjects.push_back(Note(0));
    noteObjects.push_back(Note(2));

    //huvudloop
    while (!WindowShouldClose())
    {
        cycles += 1;

        if(activeScene == 0)
        {
            if(IsKeyPressed(KEY_ENTER))
            {
                transition = true;
                cycles = 0;
            }
            drawMenu();
        }
        else if(activeScene == 1)
        {
            //har spelaren tryckt på en knapp? Flytta och animera om spelaren gjorde det
            bool playerPressedHit = playerObject.playerInput(); 
            
            //flytta varje dekoration och kontrollera om den fortfarande behövs
            for(Scenery& sc : sceneryObjects)
            {
                sc.moveScenery();
                if(sc.outOfBounds == true)
                {
                    sc.deleteScenery();
                    sc = Scenery(1);
                }
            }
            
            for(Note& nt : noteObjects)
            {
                nt.moveNote();
                if(playerPressedHit == true)
                {
                    if(playerObject.playerXPosition == nt.notePosition.x && nt.notePosition.y < -0.5f && nt.notePosition.y > -1.5f)
                    {
                        nt.outOfBounds = true;
                    }
                }
                if(nt.outOfBounds == true)
                {
                    //nt.deleteNote();
                    nt = Note(3);
                }
            }
            
            
            drawWorld(camera, playerObject, sceneryObjects, noteObjects); //rita världen
        }
        

    }

    CloseWindow();
    
}

